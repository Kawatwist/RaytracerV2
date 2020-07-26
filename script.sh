git add * &> /dev/null
git commit -m "Ready to Merge master" &> /dev/null
git push &> /dev/null
clear
echo "Files Pushed on branch Luwargni\nMerge Complete 10%"
git checkout master &> /dev/null
git pull &> /dev/null
clear
echo "Master is Update\nMerge Complete 25%"
git checkout luwargni &> /dev/null
git pull origin master &> /dev/null
clear
echo "Master on Luwargni\nMerge Complete 50%"
git add * &> /dev/null
git commit -m "Merge" &> /dev/null
git push &> /dev/null
clear
echo "Pushed merge on luwargni\nMerge Complete 70%"
git checkout master &> /dev/null
git merge luwargni &> /dev/null
clear
echo "Master merged\nMerge Complete 90%"
git checkout luwargni &> /dev/null
echo "Luwargni is Update\nMerge Complete 100%"
