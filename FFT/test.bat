@echo off
gen > in
testing < in > o1
bad < in > o2
fc o1 o2 > result
if errorlevel 1 goto fail
echo ok
test
:fail
echo yoo
