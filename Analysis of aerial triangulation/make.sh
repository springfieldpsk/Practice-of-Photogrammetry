g++ -c ./program/Matrix.cpp -o ./buildfile/Matrix
g++ -c ./program/main.cpp -o ./buildfile/main
g++ -c ./program/checkpt.cpp -o ./buildfile/checkpt
g++ -c ./program/control_pt.cpp -o ./buildfile/control_pt
g++ -c ./program/ptopoint.cpp -o ./buildfile/ptopoint
g++ -c ./program/readfromfile.cpp -o ./buildfile/readfromfile
g++ -c ./program/Auxiliary_coordinate.cpp -o ./buildfile/Auxiliary_coordinate
g++ -c ./program/Relative_orientation.cpp -o ./buildfile/Relative_orientation
g++ -c ./program/modelpoint.cpp -o ./buildfile/modelpoint
g++ -c ./program/air_belt_network.cpp -o ./buildfile/air_belt_network
g++ -c ./program/air_belt_inf.cpp -o ./buildfile/air_belt_inf
g++ -c ./program/Absolute_orientation.cpp -o ./buildfile/Absolute_orientation
g++ -c ./program/Image_control_point.cpp -o ./buildfile/Image_control_point
g++ ./buildfile/main ./buildfile/Matrix ./buildfile/checkpt ./buildfile/control_pt ./buildfile/ptopoint ./buildfile/readfromfile ./buildfile/Auxiliary_coordinate ./buildfile/Relative_orientation ./buildfile/modelpoint ./buildfile/air_belt_network ./buildfile/air_belt_inf ./buildfile/Absolute_orientation ./buildfile/Image_control_point -o run
# rm ./buildfile/Matrix
# rm ./buildfile/checkpt
# rm ./buildfile/control_pt
# rm ./buildfile/ptopoint
# rm ./buildfile/readfromfile
# rm ./buildfile/Auxiliary_coordinate
# rm ./buildfile/Relative_orientation
# rm ./buildfile/modelpoint
# rm ./buildfile/air_belt_network
# rm ./buildfile/air_belt_inf
# rm ./buildfile/Absolute_orientation
# rm ./buildfile/Image_control_point
# rm ./buildfile/main
