# minixscheduler

Just go to the directory of the runAndKillAll.sh file, and execute the command "bash -x runAndKillAll.sh"
The script expects the folders 'fibonacci/' and 'factorization/' exist in the same folder. It also expects
the object files to be under those directories. After running one program in the background, it records it's
pid, this will later be used in order to kill the process.

copyFiles.sh will move all the generated files to the folder given as an argument.

Processes run for 10 minutes.
