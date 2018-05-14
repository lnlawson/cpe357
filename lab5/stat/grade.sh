#!/bin/bash
echo "~getaylor-grader/copy/grade$1.sh ."
~getaylor-grader/copy/grade"$1".sh "."
cat "Score"
