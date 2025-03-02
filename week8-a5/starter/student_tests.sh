#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "echo tom,    and jerry" {
  run ./dsh <<EOF
echo hello
exit
EOF
  [ "$status" -eq 0 ]
  [[ "$output" == *"hello"* ]]
}

@test "uname -a" {
  run ./dsh <<EOF
uname -s
exit
EOF
  [ "$status" -eq 0 ]
  [ -n "$output" ]
}


@test "exit cmd works" {
  run ./dsh <<EOF
exit
EOF
  [ "$status" -eq 0 ]
  [[ "$output" == *"cmd loop returned"* ]]
}

@test "cd to a temp directory" {
  tmpdir=$(mktemp -d)
  run ./dsh <<EOF
cd $tmpdir
pwd
exit
EOF
  [ "$status" -eq 0 ]
  [[ "$output" == *"$tmpdir"* ]]
  rm -r "$tmpdir"
}

@test "cd with no argument" {
  run ./dsh <<EOF
cd
exit
EOF
  [ "$status" -eq 0 ]
  [[ "$output" == *"cmd loop returned"* ]]
}

@test "rc cmd returns 0 after echo" {
  run ./dsh <<EOF
echo hello
rc
exit
EOF
  [ "$status" -eq 0 ]
  [[ "$output" == *"0"* ]]
}

@test "echo \"hello world\"" {
  run ./dsh <<EOF
echo "hello world"
exit
EOF
  [ "$status" -eq 0 ]
  [[ "$output" == *"hello world"* ]]
}

@test "pipeline w/ two cmds: ls | grep .md" {
  run ./dsh <<EOF
ls | grep ".c"
exit
EOF
  [ "$status" -eq 0 ]
  [[ "$output" == *".c"* ]]
}

@test "pipeline w/ three cmds: cat dshlib.c | grep '#include' | grep stdio" {
  run ./dsh <<EOF
cat dshlib.c | grep "#include" | grep stdio
exit
EOF
  [ "$status" -eq 0 ]
  [[ "$output" == *"#include <stdio.h>"* ]]
}

@test "pipe w/ echo \"hello|world\"" {
  run ./dsh <<EOF
echo "hello|world"
exit
EOF
  [ "$status" -eq 0 ]
  [[ "$output" == *"hello|world"* ]]
}

@test "nonexistent cmd" {
  run ./dsh <<EOF
nosuchcommand
exit
EOF
  [ "$status" -ne -5 ]
  [[ "$output" == *"error: execution failed: No such file or directory"* || "$output" == *"not found"* ]]
}


@test "cmd with extra spaces: echo    hello      world" {
  run ./dsh <<EOF
echo    hello      world
exit
EOF
  [ "$status" -eq 0 ]
  [[ "$output" == *"hello world"* ]]
}

@test "piping w/ echo hello world testing | grep hello" {
  run ./dsh <<EOF
echo hello | grep hello
exit
EOF
  [ "$status" -eq 0 ]
  [[ "$output" == *"hello"* ]]
}
