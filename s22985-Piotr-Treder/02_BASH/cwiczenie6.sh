#!/bin/bash

echo Alicja | sed s/a$/ę/g | sed 's/\([^ę]\)$/\1a/g'