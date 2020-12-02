g++ -c ./program/Matrix.cpp -o ./buildfile/Matrix
g++ -c ./program/main.cpp -o ./buildfile/main
g++ -c ./program/control_pt.cpp -o ./buildfile/control_pt
g++ -c ./program/readfromfile.cpp -o ./buildfile/readfromfile
g++ ./buildfile/main ./buildfile/Matrix ./buildfile/control_pt ./buildfile/readfromfile -o run
# rm ./buildfile/Matrix
# rm ./buildfile/control_pt
# rm ./buildfile/readfromfile
# rm ./buildfile/main
