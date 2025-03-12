#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "Example: check ls runs without errors" {
    run ./dsh <<EOF                
ls
EOF

    # Assertions
    [ "$status" -eq 0 ]
}

@test "echo a simple string" {
    run ./dsh <<EOF
echo Tom & Jerry
EOF

    [ "$status" -eq 0 ]
    [[ "$output" == *"Tom & Jerry"* ]]
}

@test "change directory, then remove directory" {
        run "./dsh" <<EOF
cd dsh-test
cd ..
rm dsh-test
EOF

        [ "$status" -eq 0 ]
}

@test "pwd outputs current directory" {
    current_dir=$(pwd)
    run ./dsh <<EOF
pwd
EOF

    [ "$status" -eq 0 ]
    [[ "$output" == *"$current_dir"* ]]
}

@test "cat displays file contents" {
    tmpfile="temp_test_file.txt"
    echo "this is a test file." > "$tmpfile"

    run ./dsh <<EOF
cat $tmpfile
EOF

    [ "$status" -eq 0 ]
    [[ "$output" == *"this is a test file."* ]]
    rm -f "$tmpfile"
}



@test "returns last command exit status" {
    run ./dsh <<EOF
ls
rc
EOF

    [ "$status" -eq 0 ]
    [[ "$output" == *"0"* ]]
}


@test "change directory and pwd retunrs" {
    tmpdir="temp_dsh_test_dir"
    mkdir -p "$tmpdir"
    
    run ./dsh <<EOF
cd $tmpdir
pwd
EOF

    [ "$status" -eq 0 ]
    [[ "$output" == *"$tmpdir"* ]]
    rmdir "$tmpdir"
}

@test "invalid cd gives an error message" {
    run ./dsh <<EOF
cd /nonexistent_directory
EOF
    [ "$status" -eq 0 ]
    [[ "$output" == *"chdir failed"* || "$output" == *"No such file"* || "$output" == *"error"* ]]
}


@test "empty command gives a warning" {
    run ./dsh <<EOF

EOF
    [ "$status" -eq 0 ]
    [[ "$output" == *"No command"* || "$output" == *"warning"* || "$output" == *"CMD_WARN_NO_CMD"* ]]
}

@test "multiple commands in one input" {
    run ./dsh <<EOF
echo first
echo second
EOF
    [ "$status" -eq 0 ]
    [[ "$output" == *"first"* && "$output" == *"second"* ]]
}


@test "Echo preserves quoted spaces" {
    run ./dsh <<EOF
    echo "hello   world"
EOF

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    [ "$status" -eq 0 ]
    [ "$output" = "hello   world" ]
}
