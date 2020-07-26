git add *
git commit -m "Ready to Merge master"
git push
git checkout master
git pull
git checkout luwargni
git pull origin master
git add *
git commit -m "Merge"
git push
git checkout master
git merge luwargni
git checkout luwargni
