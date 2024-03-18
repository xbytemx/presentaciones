<!-- .slide: data-background="./img/cover.jpg"; -->
## sudo make deploy-cloudsec
#### Tony Palma


---
### $ whoami

<div> 👋 From Yucatán <img src="./img/bandera.jpg" alt="bandera de la hermana republica :v" width="4%" height="auto"><BR><img src="./img/tacos.jpg" alt="" width="15%" height="auto"> <img src="./img/playa.jpg" alt="" width="15%" height="auto"> <img src="./img/ceviche.jpg" alt="" width="15%" height="auto"> <img src="./img/mtb.jpg" alt="" width="11%" height="auto"> <img src="./img/yucatux.jpg" alt="" width="8%" height="auto"> <img src="./img/chuburna.jpg" alt="" width="15%" height="auto"></div><!-- .element: class="fragment" -->

FLOSS (Debian since 2006) <!-- .element: class="fragment" -->

Cloud Security (AWS, GCP, Azure)</div><!-- .element: class="fragment" -->

Lead Security Systems Engineer @ EPAM Systems <!-- .element: class="fragment" -->


---
### 🗂️ Agenda (1/2)

- **Cloud Security** (surprise!)
- The value of the *low-hanging* fruits (thx h1)
- *DIY* and make your own tools
- Cloud Security Engineering
  - Infrastructure as Code (**IaC**)
  - Event-Driven Architecture
  - Cloud Native
- Fixing S3 bucket subdomain takeovers


---
### 🗂️ Agenda (2/2)

- Challenges of a secure multicloud approach
  - Secure baseline for AWS Accounts, GCP Projects, Azure Subscriptions
  - Who is the owner of this resource? *Tag Enforcement*
  - Who should be informed? *Majordomo*
  - Golden Images
- CloudSec Roadmap


---
<!-- .slide: data-background="./img/titles.png"; -->
## Quick talk about Cloud Security


---
### Quick Definition

> Cloud security is the set of cybersecurity measures used to protect cloud-based applications, data, and infrastructure. 
> 
> [https://cloud.google.com/learn/what-is-cloud-security](https://cloud.google.com/learn/what-is-cloud-security#section-2)



---
### Now on CloudSec

<img src="./img/current-state.png" width="75%" height="auto">

###### [Current state of Cloud Security, CSHub 2023](https://www.cshub.com/cloud/reports/the-future-of-cloud-security)


---
### Base solutions for Cloud Security

- CSPM:  Cloud Security Posture Management
- CWPP:  Cloud Workload Protection Platform
- CIEM:  Cloud Infrastructure Entitlements Management
- CNAPP: Cloud-Native Application Protection Platform


---
<!-- .slide: data-background="./img/titles.png"; -->
## The value of the low-hanging fruits (thx h1)


---
### A few years ago ...

- Automated tools to detect miss-configuration and made the takeover <!-- .element: class="fragment" -->
- In scope, but who is the owner? <!-- .element: class="fragment" -->
- Leaks <!-- .element: class="fragment" -->
- Mergers and Acquisitions (M&A) <!-- .element: class="fragment" -->
- log4j u.u <!-- .element: class="fragment" -->


---
<!-- .slide: data-background="./img/titles.png"; -->
## Do it yourself (DIY) and made your own tools


---
### Fight fire with fire

- Most of cloud tools are not custom-made, unless its yours <!-- .element: class="fragment" -->
- Challenging and will not be for everyone <!-- .element: class="fragment" -->
- Dev + SEC + Ops <!-- .element: class="fragment" -->
- Cloud Security Reviews <!-- .element: class="fragment" -->
- The gap between security team capacity and cloud security needs is huge <!-- .element: class="fragment" -->


#### Cloud security;  <!-- .element: class="fragment" --> **Self Service**  <!-- .element: class="fragment highlight-blue" --> and **Flexible**?  <!-- .element: class="fragment highlight-blue" -->


---
### Cloud Security is a team game: Key players

- GRC (Governance, Risk, Compliance)
- Vulnerability Management
- Security Operations
- IAM
- DevOps
- Dev teams with Security Champions


---
<!-- .slide: data-background="./img/titles.png"; -->
## Cloud Security Engineering


---
### Infrastructure as Code

- AWS CloudFormation, Azure Resource Manager, Google Cloud Deployment Manager
- Cloud Agnostic
  - Terraform ⭐
  - Pulumi
  - Crossplane
  - OpenTofu 👀


---
### Use the Security stone on Iac?

![pikachu and the thunderstone](./img/pikachu-thunderstone.jpg)


---
### What? IaC is evolving!

- Unit, Contract, Integration testing (terraform)
![tf testing](./img/terraform-module_testing.webp)

- Compliance as Code (https://terraform-compliance.com/)
  - Policy as Code
- Secure Infrastructure as Code
  - Security as Code


---
### Event-Driven Architecture

> An event-driven architecture uses events to trigger and communicate between decoupled services and is common in modern applications built with microservices.
![](https://media.giphy.com/media/8wbpmeim0LmdW/giphy.gif) <!-- .element style="border: 0; background: None; box-shadow: None" width="100px" -->
Event-Driven Architecture ([EDA](https://aws.amazon.com/event-driven-architecture/))


---
### I had a similar one

- Security Orchestration, Automation and Response (SOAR)
- Security Information and Event Management (SIEM)


---
### Cloud Native

> Cloud native technologies empower organizations to build and run scalable applications in modern, dynamic environments such as public, private, and hybrid clouds. Containers, service meshes, microservices, immutable infrastructure, and declarative APIs exemplify this approach.
> 
> [https://github.com/cncf/toc/blob/main/DEFINITION.md](https://github.com/cncf/toc/blob/main/DEFINITION.md)


---
<div id="light_back">

![](./img/ERGO_eda.png) 

</div>


---

### Fixing S3 bucket subdomain takeovers


---
![](./img/diagram.s3bto.png) <!-- .element style="border: 0; background: None; box-shadow: None" width="50%" -->


---
<!-- .slide: data-auto-animate="true"; -->

```text
.
├── Makefile
├── builds
│   ├── s3to_defender
│   │   └── bootstrap
│   └── s3to_defender.zip
├── go.mod
├── go.sum
├── internal
│   └── logging.go
├── lambdas
│   └── s3to_defender
│       └── main.go
└── terraform
    ├── builds
    ├── eventbridge.tf
    ├── locals.tf
    ├── modules
    │   └── create_lambda
    │       ├── main.tf
    │       ├── outputs.tf
    │       └── variables.tf
    ├── providers.tf
    ├── s3to_defender.tf
    ├── sqs.tf
    └── terraform.tf
```
<!-- .element: data-id="code-animation" stretch-->


---
<!-- .slide: data-auto-animate="true"; -->

```make []
build:
	@cd lambdas; \
	for lambda_name in `ls .`; do \
		cd $$lambda_name; \
		GOOS=linux GOARCH=amd64 CGO_ENABLED=0 go build -ldflags='-s -w' -o ../../builds/$$lambda_name/bootstrap -tagslambda.norpc ; \
		zip ../../builds/$$lambda_name.zip ../../builds/$$lambda_name/bootstrap ; \
		cd .. ; \
	done

deploy: build
	@cd terraform ; \
	terraform init ; \
	terraform fmt -recursive && terraform validate ; \
	terraform apply -auto-approve ; \
```
<!-- .element: data-id="code-animation" -->


---
<!-- .slide: data-auto-animate="true"; -->

```hcl [|11-15|25|35-41]
#Using terraform eventbridge module
module "eventbridge" {
  source  = "terraform-aws-modules/eventbridge/aws"
  version = "3.2.3"


  bus_name = "hackgdl-event-bus"

  create_permissions = true

  attach_sqs_policy = true
  sqs_target_arns = [
    aws_sqs_queue.queue.arn,
    aws_sqs_queue.dlq.arn
  ]

  rules = {
    s3_deletebucket_events = {
      description = "Capture all S3 DeleteBucket events",
      event_pattern = jsonencode({
        "source" : ["aws.cloudtrail"],
        "detail" : {
          "eventSource" : ["s3.amazonaws.com"],
          "errorCode" : [{ "exists" : false }],
          "eventName" : ["DeleteBucket"]
        }
      })
      enabled = true
    }
  }

  targets = {
    s3_deletebucket_events = [
      {
        name            = "send-events-to-sqs"
        arn             = aws_sqs_queue.queue.arn
        dead_letter_arn = aws_sqs_queue.dlq.arn
        target_id       = "send-events-to-sqs"
      }
    ]
  }

}
```
<!-- .element: data-id="code-animation" -->


---
<!-- .slide: data-auto-animate="true"; -->

```hcl []
#Create SQS objects to allow receiving messages from eventbridge
resource "aws_sqs_queue" "dlq" {
  name = "hackgdl-dlq"
}

resource "aws_sqs_queue" "queue" {
  name = "hackgdl-queue"
}

resource "aws_sqs_queue_policy" "queue" {
  queue_url = aws_sqs_queue.queue.id
  policy    = data.aws_iam_policy_document.queue.json
}

data "aws_iam_policy_document" "queue" {
  statement {
    sid     = "AllowSendMessage"
    actions = ["sqs:SendMessage"]

    principals {
      type        = "Service"
      identifiers = ["events.amazonaws.com"]
    }

    resources = [aws_sqs_queue.queue.arn]
  }
}
```
<!-- .element: data-id="code-animation" -->



---
<!-- .slide: data-auto-animate="true"; -->

```hcl []
module "lambda_s3bto_defender" {
  source = "./modules/create_lambda"

  function_name  = "${local.basename}_s3bto_defender"
  source_path    = "../builds/s3to_defender"
  sqs_source_arn = aws_sqs_queue.queue.arn
  extra_policies = []
}
```
<!-- .element: data-id="code-animation" -->


---
<!-- .slide: data-auto-animate="true"; -->

```hcl [|5-9|13-18|31-42]
module "lambda" {
  source  = "terraform-aws-modules/lambda/aws"
  version = "7.2.2"

  function_name = var.function_name
  description   = "Lambda generated for ${var.source_path}"
  handler       = "bootstrap"
  runtime       = "provided.al2023"
  publish       = true

  source_path = var.source_path

  allowed_triggers = {
    sqs = {
      principal  = "sqs.amazonaws.com"
      source_arn = var.sqs_source_arn
    }
  }

  event_source_mapping = {
    sqs = {
      event_source_arn = var.sqs_source_arn
    }
  }

  create_current_version_allowed_triggers = false

  attach_policies    = true
  number_of_policies = 1 + length(var.extra_policies)

  policies = merge(
    ["arn:aws:iam::aws:policy/service-role/AWSLambdaSQSQueueExecutionRole"],
    var.extra_policies)

  attach_policy_statements = true
  policy_statements = {
    cloudfront = {
      effect    = "Allow",
      actions   = ["cloudfront:ListDistributions", "cloudfront:GetDistributionConfig"],
      resources = ["*"]
    }
  }

  environment_variables = {
    KILLSWITCH = "false"
  }

}
```
<!-- .element: data-id="code-animation" -->


---
<!-- .slide: data-auto-animate="true"; -->

```go []
package main

import (
	"context"
	"encoding/json"
	"fmt"

	"github.com/aws/aws-lambda-go/events"
	"github.com/aws/aws-lambda-go/lambda"
	"github.com/aws/aws-sdk-go-v2/config"
	"github.com/aws/aws-sdk-go-v2/service/cloudfront"
	"github.com/sirupsen/logrus"
	"gitlab.com/xbytemx/hackgdl/internal"
)

var log *logrus.Entry

func s3toDefender(ctx context.Context, sqsEvent events.SQSEvent) error {
	return nil
}

func main() {
	lambda.Start(s3toDefender)
}
```
<!-- .element: data-id="code-animation" -->


---
<!-- .slide: data-auto-animate="true"; -->

```go []
package main

import (
	"context"
	"encoding/json"
	"fmt"

	"github.com/aws/aws-lambda-go/events"
	"github.com/aws/aws-lambda-go/lambda"
	"github.com/aws/aws-sdk-go-v2/config"
	"github.com/aws/aws-sdk-go-v2/service/cloudfront"
	"github.com/sirupsen/logrus"
	"gitlab.com/xbytemx/hackgdl/internal"
)

var log *logrus.Entry

func s3toDefender(ctx context.Context, sqsEvent events.SQSEvent) error {
	aws_id := internal.RequestID(ctx)
	log = internal.NewLogger().WithField("aws_id", aws_id)

	if len(sqsEvent.Records) == 0 {
		log.Fatalf("received empty event")
		return fmt.Errorf("received empty event")
	}

	return nil
}

func main() {
	lambda.Start(s3toDefender)
}
```
<!-- .element: data-id="code-animation" -->


---
<!-- .slide: data-auto-animate="true"; -->

```go []
package main

import (
	"context"
	"encoding/json"
	"fmt"

	"github.com/aws/aws-lambda-go/events"
	"github.com/aws/aws-lambda-go/lambda"
	"github.com/aws/aws-sdk-go-v2/config"
	"github.com/aws/aws-sdk-go-v2/service/cloudfront"
	"github.com/sirupsen/logrus"
	"gitlab.com/xbytemx/hackgdl/internal"
)

var log *logrus.Entry

func s3toDefender(ctx context.Context, sqsEvent events.SQSEvent) error {
	aws_id := internal.RequestID(ctx)
	log = internal.NewLogger().WithField("aws_id", aws_id)

	if len(sqsEvent.Records) == 0 {
		log.Fatalf("received empty event")
		return fmt.Errorf("received empty event")
	}

	cfg, err := config.LoadDefaultConfig(context.TODO(), config.WithRegion("us-east-1"))
	if err != nil {
		log.Fatalf("unable to load SDK config, %v", err)
		return err
	}

	svc := cloudfront.NewFromConfig(cfg)
	return nil
}

func main() {
	lambda.Start(s3toDefender)
}
```
<!-- .element: data-id="code-animation" -->


---
<!-- .slide: data-auto-animate="true"; -->

```go []
package main

import (
	"context"
	"encoding/json"
	"fmt"

	"github.com/aws/aws-lambda-go/events"
	"github.com/aws/aws-lambda-go/lambda"
	"github.com/aws/aws-sdk-go-v2/config"
	"github.com/aws/aws-sdk-go-v2/service/cloudfront"
	"github.com/sirupsen/logrus"
	"gitlab.com/xbytemx/hackgdl/internal"
)

var log *logrus.Entry

func s3toDefender(ctx context.Context, sqsEvent events.SQSEvent) error {
	aws_id := internal.RequestID(ctx)
	log = internal.NewLogger().WithField("aws_id", aws_id)

	if len(sqsEvent.Records) == 0 {
		log.Fatalf("received empty event")
		return fmt.Errorf("received empty event")
	}

	cfg, err := config.LoadDefaultConfig(context.TODO(), config.WithRegion("us-east-1"))
	if err != nil {
		log.Fatalf("unable to load SDK config, %v", err)
		return err
	}

	svc := cloudfront.NewFromConfig(cfg)

	for _, message := range sqsEvent.Records {
		var event map[string]interface{}
		json.Unmarshal([]byte(message.Body), &event)

		dists, err := svc.ListDistributions(context.TODO(), &cloudfront.ListDistributionsInput{})
		if err != nil {
			log.Fatalf("unable to list dists, %v", err)
			return err
		}

		for _, dist := range dists.DistributionList.Items {
			output, err := svc.GetDistributionConfig(context.TODO(), &cloudfront.GetDistributionConfigInput{Id: dist.Id})
			if err != nil {
				log.Fatalf("unable to get dist config, %v", err)
				return err
			}
			for _, origin := range output.DistributionConfig.Origins.Items {
	...
			}
		}

	}
	return nil
}

func main() {
	lambda.Start(s3toDefender)
}
```
<!-- .element: data-id="code-animation" -->


---
<!-- .slide: data-background="./img/titles.png"; -->
## Challenges of multicloud security


---
### Secure baseline configurator for AWS Accounts, GCP Projects, Azure Subscriptions

- Configure roles for security services (remediation, monitoring, operations, etc)
- GitOps; control infra changes from code
- Onboarding and offboarding!
- Cloud-Agnostic Approach
- **Remember:** Account level configuration (MFA, Logs, Costs, IAM, etc)


---
### Tag Enforcement

- Hey CFO!
- Service Catalog
- How many days should you wait for a team to tag their assets?
- Detect, notify, destroy.
- REALLY, DESTROY!<!-- .element: class="fragment" -->
- But first, a backup. Then is time to nuke <!-- .element: class="fragment" -->


---
### Majordomo

- First Point of Contact.
- More GitOps
- Trusted source
- Distribution lists
- Communication channels (slack, opsgenie, etc)
- Alerts and notifications


---
<!-- .slide: data-background="./img/titles.png"; -->
## Golden Images


---
### Made your own Golden Images for multiple CSP

- Same base OS
- Available for All
- Hardening
- Security tools
- Easy to integrate


---
<!-- .slide: data-background="./img/titles.png"; -->
## Cloud Security Roadmap


---
### Cloud Service Providers (1/2)

- AWS
  - AWS Cloud Practitioner 
  - AWS Solution Architect Associate (SAA)
  - AWS Security Speciality
- GCP
  - Associate Cloud Engineer (ACE)
  - Professional Solution Architect (PSA)
  - Professional Cloud Security Engineer (PCSE)


---
### Cloud Service Providers (1/2)

- Azure
  - AZ-900: Microsoft Azure Fundamentals
  - AZ-500: Microsoft Azure Security Technologies
  - AZ-104: Microsoft Azure Administrator
  - AZ-303 and AZ-304: Microsoft Azure Architect Technologies & Design 


---
### Must-read CSP Frameworks

- AWS Well-Architected Framework
- Google Cloud Architecture Framework
- Azure Well-Architected Framework


---
### Technology Stack

- Infrastructure as Code: Terraform, Pulimi
  - Terraform: Up and Running
- Configuration Management: Ansible, Puppet
  - Ansible for DevOps
- Programming languages for cloud-native: Go, Python
  - The Go Programming Language
  - 100 Go Mistakes and How to Avoid Them
- CI/CD: Github Actions, Jenkins
  - Automating DevOps with GitLab CI/CD Pipelines


---
### Extra Books!

- Security as Code
- Container Security
- Architecting Cloud-Native Serverless Solutions
- Cloud Auditing Best Practices
- Building Event-Driven Microservices
- Software Engineering at Google
- Fundamentals of Software Architecture
- Software Architecture: The hard parts


---
## Thanks!
#### Questions?

###### @xbytemx
