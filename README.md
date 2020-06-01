|                                                                                                                                Codacy                                                                                                                                |                                                     License                                                     |                                                                                                         Twitter                                                           |
| :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------: | :--------------------------------------------------------------------------------------------------------------------------: |
| [![Codacy Badge](https://api.codacy.com/project/badge/Grade/903858d5d0f649729b2364e0e96dabc6)](https://app.codacy.com/app/hungrybluedev/C-Programs?utm_source=github.com&utm_medium=referral&utm_content=hungrybluedev/C-Programs&utm_campaign=Badge_Grade_Settings) | ![GitHub](https://img.shields.io/github/license/hungrybluedev/C-Programs) |  [![Twitter URL](https://img.shields.io/twitter/url/https/hungrybluedev.svg?style=social)](https://twitter.com/HungryBlueDev) |

# C Programs

-   [C Programs](#c-programs)
    -   [Introduction](#introduction)
    -   [Motive](#motive)
    -   [How to use these programs?](#how-to-use-these-programs)
    -   [A Note on Unit Tests](#a-note-on-unit-tests)
    -   [How can I help?](#how-can-i-help)
    -   [List of Programs](#list-of-programs)

## Introduction

This repository is a collection of C programs that are meant to be
used as reference or reused (with the proper licenses, included
alongside the sources, for easy distribution). I encourage people to
explore the source code and learn from them, rather than simply copy
and paste it into their work. C is a particularly difficult language
because the programmer must pay close attention to fine details. I
try to document as much as I can right into the source code, in
addition to the READMEs and other Markdown files.

## Motive

My intention is to educate beginners, besides just solving particular
programming problems. I hope that the extra comments and instructions
that I have included in my work are useful and serve their purpose:
to guide and educate. This work is liberally licensed under the
MIT License, therefore, fellow developers can reuse this code in their
projects as long they provide attribution and follow the (very lenient)
terms of use, you should be grand.

## How to use these programs

This is not meant to be a project that creates one (or a set number) of
binaries that can be executed. It is merely a collection of different types
of programs, with different problems to solve. Consequently, it doesn't make
sense to create a single makefile to compile all the sources into libraries.

The project organization is important. All programs are self-contained in
their respective folders. Take the entire folder and put it in your project.
The licences are already there, along with the READMEs, so there's a lot of
effort saved. This is a modular project. With independent units. Pick and
choose to suit your needs.

## A Note on Unit Tests

Throughout the project, I have made use of [John Brewer's](http://www.jera.com/),
MinUnit - a minimal unit testing framework for C. Find it [here](http://www.jera.com/techinfo/jtns/jtn002.html).

The reason I used this and not more established test suites is because of
its ridiculous simplicity and plug-and-play nature. It is a completely header-based
unit testing framework and writing unit tests is super easy. Check any of my
`test.c` files and you will agree. Having this ensures that people will have less
excuses not to unit test their code. Even if it's C.

## Recommended Software and Services

The programs are meant to be cross-platform. Here is a list of relevant programs
and services I use:
1.  [**CLion**](https://www.jetbrains.com/clion/) - This is my IDE of choice whenever I work on large projects. Whenver I can
    afford to install CLion, I do. I am currently using my students' benefit to  evaluate this software for free.
    I intend to get a CLion license for all contributors of this project, if there's enough interest.

2.  [**Visual Studio Code**](https://code.visualstudio.com/) - It has reached a level of
    maturity and acceptance that makes it well suited to be a daily-driver. Through the
    use of extensions, it can be customised to suit almost all needs. Some of the
    extensions that I use are:

-   The default [C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) from Microsoft
-   [Comment Anchors](https://marketplace.visualstudio.com/items?itemName=ExodiusStudios.comment-anchors) from Exodius Studios
-   [Remark](https://marketplace.visualstudio.com/items?itemName=mrmlnc.vscode-remark) from mrmlnc

3.  [**Scoop**](https://scoop.sh/) - A package manager for Windows. I use it to install
    all command line tools and utilities, including, but not limited to:

-   Git
-   GCC (and MinGW)

4.  [**Codacy**](https://www.codacy.com/) - A code quality monitoring service that is
    free for open source projects, such as this one. It is very helpful as it catches
    slip-ups or mistakes that unit tests are unable to cover.

## How can I help

If you feel that this project was of (at least some) help to you, and
you want to repay me, then here's how to do it:

1.  **Fix errors via Issues or Pull Requests** - If you come across any error,
    (intentional or not) you may raise an _Issue_. I will fix the Issue as
    soon as is possible for me to do. If you want to do it yourself, consider
    submitting a _Pull Request_ with the updated code. 
2.  **Contribute code (with the same license as I do)** - There will obviously
    be several prorgams that are not currently present in this archive. You
    may generously add your own implementations (with proper documentation)
    via a _Pull Request_.
3.  **Consider financially supporting me** - It takes a lot of time and effort
    to ensure that the programs I write here are of the highest quality possible.
    If you benefitted from this project and have the means to provide some support
    financially, you can do so via a monthly donation on
    [Patreon](https://www.patreon.com/hungrybluedev) or a one time donation on
    [PayPal](https://www.paypal.me/hungrybluedev).

## List of Programs

1.  [ArrayList](https://github.com/hungrybluedev/C-Programs/tree/master/Data%20Structures/ArrayList) - A dynamic, random-access array-based List implementation.
2. [Panic](https://github.com/hungrybluedev/C-Programs/tree/master/StdLib/Panic) - A library that the program can call when a state of panic happens and we want to guarantee a graceful exit.
3. [String](https://github.com/hungrybluedev/C-Programs/tree/master/StdLib/String) - A safe, length prefixed string implementation with lots of utility methods. Inspired by [nybbles.io's](https://www.youtube.com/channel/UCaV77OIv89qfsnncY5J2zvg) first video in the CKong series: [C11: [CKong] C introduction](https://www.youtube.com/watch?v=1KHVphJm6PU&t=109s).

