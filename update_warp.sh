#bin/bash
set -e

git submodule update --remote warp

if git diff --quiet -- warp; then
    echo "No changes in warp"
    exit 0
fi

git add warp
git commit -m "Update warp"
git push

echo "warp updated successfully"