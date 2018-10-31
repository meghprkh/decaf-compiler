#!/usr/bin/env bash

# Displays AST graphs using mermaid.cli

FILE="$1"

if [ $# -eq 0 ]; then
  cat >tmphelper
  FILE="tmphelper"
fi

./decaf "$FILE" >tmpout
mmdc -i tmpout -o tmpout.svg
firefox tmpout.svg 2>/dev/null 1>&2
