# Contributing to shmem4py

Thanks for taking the time to contribute!

## Table of Contents

- [I Have a Question](#i-have-a-question)
- [I Want To Contribute](#i-want-to-contribute)
  - [Reporting Bugs](#reporting-bugs)
  - [Suggesting Enhancements](#suggesting-enhancements)

## I Have a Question

> If you want to ask a question, we assume you have read the available [documentation](https://shmem4py.readthedocs.io/).

Before you ask a question, it is best to search for existing [Issues](/issues) that might help you. In case you have found a suitable issue and still need clarification, you can write your question in this issue. It is also advisable to search the internet for answers first. Please note that many questions regarding the programming model itself and suggestions for its enhancements may better belong to the [OpenSHMEM Community](http://openshmem.org/site/Community) rather than the shmem4py project, which is naturally constrained by the specification and underlying OpenSHMEM implementations.

If you still feel the need to ask a question or clarification, we recommend opening an [Issue](/issues/new). Please remember to provide as much context as possible about what you're running into and report project and platform versions depending on what seems relevant.

We will then take care of the issue as soon as possible.

## I Want To Contribute

> ### Legal Notice
> When contributing to this project, you must agree that you have authored 100% of the content, have the necessary rights, and that the content you contribute may be provided under the project license.

### Reporting Bugs

#### Before Submitting a Bug Report

A good bug report shouldn't leave others needing to chase you for more information. Therefore, we ask you to investigate carefully, collect information and describe the issue in detail in your report. Please complete the following steps in advance to help us fix any potential bug quickly:

- Make sure that you are using the latest version.
- Determine if your bug is really a bug and not an error on your side, e.g., using incompatible environment components/versions (Make sure that you have read the [documentation](https://shmem4py.readthedocs.io/).
- To see if other users have experienced (and potentially already solved) the same issue you are having, check if there is not already a bug report existing for your bug or error in the [bug tracker](issues?q=label%3Abug).
- Also, make sure to search the internet (including Stack Overflow) to see if users outside of the GitHub community have discussed the issue.
- Collect information about the bug:
  - Stack trace (Traceback)
  - OS, Platform and Version (Windows, Linux, macOS, x86, ARM)
  - Version of the Python, Python packages, OpenSHMEM implementation, etc., depending on what seems relevant.
  - Possibly your input and the output
  - Can you reliably reproduce the issue? And can you also reproduce it with older versions?
- If possible, check if the same issue can be reproduced in C rather than Python. If that is the case, the issue is often with the underlying OpenSHMEM implementation, not shmem4py.

#### How Do I Submit a Good Bug Report?

We use GitHub issues to track bugs and errors. If you run into an issue with the project:

- Open an [Issue](/issues/new).
- Explain the behavior you would expect and the actual behavior.
- Please provide as much context as possible and describe the *reproduction steps* that someone else can follow to recreate the issue on their own. This usually includes your code. For good bug reports, you should isolate the problem and create a reduced test case.
- Provide the information you collected in the previous section.

Once it's filed:

- A team member will try to reproduce the issue with your provided steps. If there are no reproduction steps or no obvious way to reproduce the issue, the team will ask you for those steps and mark the issue as `needs-repro`. Bugs with the `needs-repro` tag will not be addressed until they are reproduced.
- If the team is able to reproduce the issue, it will be marked `needs-fix`, as well as possibly other tags (such as `critical`), and worked on as soon as time allows.

### Suggesting Enhancements

This section guides you through submitting an enhancement suggestion for shmem4py, including completely new features and minor improvements to existing functionality. Following these guidelines will help maintainers and the community to understand your suggestion and find related suggestions.


#### Before Submitting an Enhancement

- Make sure that you are using the latest version.
- Read the [documentation](https://shmem4py.readthedocs.io/) carefully and find out if the functionality is already covered, maybe by an individual configuration.
- Perform a [search](/issues) to see if the enhancement has already been suggested. If it has, add a comment to the existing issue instead of opening a new one.
- Find out whether your idea fits with the scope and aims of the project. It's up to you to make a strong case to convince the project's developers of the merits of this feature. Keep in mind that we want features that will be useful to the majority of our users and not just a small subset. If you're just targeting a minority of users, consider writing an add-on/plugin library.
- Consider whether your suggestion applies to shmem4py or [OpenSHMEM](http://openshmem.org/).


#### How Do I Submit a Good Enhancement Suggestion?

Enhancement suggestions are tracked as [GitHub issues](/issues).

- Use a **clear and descriptive title** for the issue to identify the suggestion.
- Provide a **step-by-step description of the suggested enhancement** in as many details as possible.
- **Describe the current behavior** and **explain which behavior you expected to see instead** and why. At this point, you can also tell which alternatives do not work for you.
- **Explain why this enhancement would be useful** to most shmem4py users. You may also want to point out the other projects that solved it better and which could serve as inspiration.

## Attribution
This guide is based on the **contributing.md**. [Make your own](https://contributing.md/)!
