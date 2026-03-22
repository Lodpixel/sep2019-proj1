VS Code configuration rollback guide

This project run/debug setup only changed VS Code config files.

Changed files:
- .vscode/settings.json
- .vscode/tasks.json
- .vscode/launch.json
- .vscode/extensions.json

Quick rollback with git (recommended):
1) Restore tracked files:
   git restore .vscode/settings.json
2) Remove newly added files:
   git clean -f .vscode/tasks.json .vscode/launch.json .vscode/extensions.json .vscode/RECOVERY.md

If you want to keep recommendations but remove run/debug setup, delete only:
- .vscode/tasks.json
- .vscode/launch.json

Notes:
- Build failures from project source code are unrelated to these VS Code configs.
- Current build error references Snake constructor signature mismatch in snake.cpp/snake.h and gamecore/multigame call sites.
