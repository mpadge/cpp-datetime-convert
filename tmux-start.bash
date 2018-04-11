#!/bin/sh

SESSION="datetime"

tmux -2 new-session -d -s $SESSION

tmux new-window -t $SESSION:1 -k -n datetime
tmux send-keys -t $SESSION:1 'vim datetime.h' C-m
tmux send-keys -t $SESSION:1 ':' 'tabe datetime.cpp' C-m
tmux send-keys -t $SESSION:1 ':' 'tabe main.cpp' C-m
tmux send-keys -t $SESSION:1 '1gt'
tmux split-window -h -p 50
#tmux send-keys -t $SESSION:1 'make' C-m
tmux select-pane -t 0

tmux new-window -t $SESSION:2 -n datetime-make
tmux select-window -t $SESSION:2
tmux send-keys -t $SESSION:2 'vim tmux-start.bash' C-m
tmux send-keys -t $SESSION:2 ':' 'tabe makefile' C-m
tmux send-keys -t $SESSION:2 ':' 'tabe .travis.yml' C-m
tmux send-keys -t $SESSION:2 ':' 'tabe README.md' C-m
tmux split-window -h
tmux send-keys -t $SESSION:2 'git status' C-m
tmux select-pane -t 0

tmux select-window -t $SESSION:1

tmux attach -t $SESSION
