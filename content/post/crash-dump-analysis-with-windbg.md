---
title: "Crash dump analysis with windbg"
date: 2020-01-13T19:16:27+08:00
draft: false
tags: [windbg, dump]
categories: [C++, debug]
---
Introduce basic steps for using windbg.

# Steps of crash dump analysis with windbg

## .exr -1

The *.exr* command displays the contents of an exception record (a **EXCEPTION_RECORD** structure).

The [**EXCEPTION_RECORD**](https://docs.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-exception_record) structure contains the *Instruction Address* (the function raising the exception), the *Exception Code*, and (max 15) *Exception Parameters*.

0x80000003 is break point exception.

## .lastevent

displays the most recent exception or event that occurred.

## !analyze -v

## .symopt+ 0x40

force load symbols

## .reload -f -i <module_name>

force load symbol names for specified module.
