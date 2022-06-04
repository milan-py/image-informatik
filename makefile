output: imgui_draw.o imgui_widgets.o imgui.o imgui_tables.o imgui-SFML.o imgui_demo.o main.o hidden.o
	g++ main.o imgui_draw.o imgui_widgets.o imgui.o imgui_tables.o imgui-SFML.o imgui_demo.o hidden.o -o bin\displayer.exe -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -lopengl32 

imgui_draw.o: lib\imgui_draw.cpp
	g++ lib\imgui_draw.cpp -c -I include/ 
imgui_widgets.o: lib\imgui_widgets.cpp
	g++ lib\imgui_widgets.cpp -c -I include/ 
imgui.o: lib\imgui.cpp
	g++ lib\imgui.cpp -c -I include/
imgui_tables.o: lib\imgui_tables.cpp
	g++ lib\imgui_tables.cpp -c -I include/ 
imgui-SFML.o: lib\imgui-SFML.cpp
	g++ lib\imgui-SFML.cpp -c -I include/ 
imgui_demo.o: lib\imgui_demo.cpp
	g++ lib\imgui_demo.cpp -c -I include/

hidden.o: hidden.cpp
	g++ hidden.cpp -c -std=c++17
main.o: main.cpp
	g++ main.cpp -c -I include/ -std=c++17



  

