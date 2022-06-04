# image-informatik

[Bildformat](https://www.inf-schule.de/kids/datennetze/pixelgrafik/schritt7)

In dem Ordner "bin" befinden sich die .exe und .dll Dateien die man brauch um die Programme laufen zu lassen

## displayer.exe
Nimmt als Konsolenargument einen Dateinamen zu einer Datei im PPM Format.
Diese Wird gelesen und in einem [sfml](https://github.com/SFML/SFML) Fenser abgebildet. 
Mithilfe von [imgui](https://github.com/ocornut/imgui) und [imgui-sfml](https://github.com/eliasdaler/imgui-sfml) wird in einem kleinem Fenster die größe des Bildes und der möglicherweise versteckte Text angezeigt.

## writer.exe
Versteckt einen string **ohne** Leerzeichen in einer PPM-Datei mit gegebener Pixelbreite 
