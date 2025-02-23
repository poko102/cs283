#!/usr/bin/env bats

@test "exit command terminates shell" {
  run ./dsh <<< "exit\n"
  [ "$status" -eq 0 ]
}

@test "cd command changes directory" {
  # Save current directory to restore later.
  current=$(pwd)
  # Change to /tmp and create a test directory.
  cd /tmp
  mkdir -p dsh-test
  # Run the shell using its absolute path so it inherits /tmp as its working directory.
  run "${current}/dsh" <<EOF
cd dsh-test
pwd
exit
EOF
  # Restore the original directory.
  cd "$current"
  [ "$status" -eq 0 ]
  # Check that the output contains "/tmp/dsh-test"
  [[ "$output" =~ "/tmp/dsh-test" ]]
}
