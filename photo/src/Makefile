# INCLUDES_H = /root/Codes/robot/arm/photo/include/includes.h 

main: binary_photo.o binary.o deonising.o edge.o /root/Codes/robot/arm/photo/include/includes.h
	g++ -g -o ${@} $^  `pkg-config opencv --cflags --libs `

binary_photo.o: binary_photo.cpp binary.o /root/Codes/robot/arm/photo/include/includes.h
	g++ -c -g $< `pkg-config opencv --cflags --libs `

binary.o: binary.cpp /root/Codes/robot/arm/photo/include/binary.h /root/Codes/robot/arm/photo/include/includes.h
	g++ -c -g $< `pkg-config opencv --cflags --libs `

deonising.o: deonising.cpp /root/Codes/robot/arm/photo/include/deonising.h /root/Codes/robot/arm/photo/include/includes.h
	g++ -c -g $< `pkg-config opencv --cflags --libs `	

edge.o: edge.cpp /root/Codes/robot/arm/photo/include/edge.h /root/Codes/robot/arm/photo/include/deonising.h /root/Codes/robot/arm/photo/include/includes.h
	g++ -c -g $< `pkg-config opencv --cflags --libs `		

			
clean:

	rm *.o main
