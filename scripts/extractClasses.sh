#!/bin/bash

egrep '^/' $1 | awk '{ print $3; }' | sort | uniq | gawk '/.*/ { print gensub(/N8solidity8frontend[0-9]*([a-zA-Z]*)E/, "\\1", "g", $0); }' | egrep '.' | sort
