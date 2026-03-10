#!/bin/bash
CUR_TIME=$(date +%m_%d_%y_%H:%M:%S)
mkdir ~/backup/$CUR_TIME

rsync  -avz  ~/* --filter='exclude backup/' --filter='exclude test/' ~/backup/$CUR_TIME 
