#!/bin/bash

if [[ "$1" == "--debug" ]]; then
    ./build.sh
    echo -e "\n\n"
    ./build/bin/JotaEngine
    echo -e "\n\n"

elif [[ "$1" == "--release" ]]; then
    ./build.sh
    clear
    ./build/bin/JotaEngine
    clear

else
    clear
    echo "./run.sh - Uso incorreto!"
    echo "Use um dos seguintes modos:"
    echo "  --debug     # Executa em modo debug (pula linha)"
    echo "  --release   # Executa em modo release (limpa o terminal)"
    exit 1
fi
