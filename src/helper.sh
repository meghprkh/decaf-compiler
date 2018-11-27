#!/usr/bin/env bash

# Displays AST graphs using mermaid.cli

FILE="$1"

if [ $# -eq 0 ]; then
  cat >tmphelper
  FILE="tmphelper"
fi

./decaff "$FILE" 2>tmp.ll
# mmdc -i tmp.mermaid -o tmpout.svg
# firefox tmpout.svg 2>/dev/null 1>&2
echo; echo; echo '###### LLVM IR ######'; echo; echo
cat tmp.ll

echo; echo; echo '###### Executing IR ######'; echo; echo
lli tmp.ll
