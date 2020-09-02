from graphics import *
from tkinter import *
import math

def get_bin(x, n=5):
    return format(x, 'b').zfill(n)

image = [
        get_bin(5) +"000", 
        get_bin(9) +"000",
        get_bin(11) +"000",
        get_bin(13) +"000",
        get_bin(15) +"000",
        get_bin(16) +"001",
        get_bin(17) +"000",
        get_bin(18) +"000",
        get_bin(18) +"000",
        get_bin(18) +"000",
        get_bin(18) +"000",
        get_bin(18) +"000",
        get_bin(19) +"000",
        get_bin(18) +"101",
        get_bin(20) +"101",
        get_bin(20) +"101",
        get_bin(21) +"101",
        get_bin(22) +"101",
        ]

def bitstr2hex(bitstr):
    bitstr = bitstr
    return "0x%x" % int(bitstr,2)

def writeimg(img):
    print("{",end = '' )
    print(', '.join(map(bitstr2hex, img)) + '}')

def bitRead(string,pos):
    last = len(string) - 1;
    return int(string[last - pos])

def drawPixel(x,y):
    x = x*4
    y = y*4
    Point(x, y).draw(win)
    Point(x+1, y).draw(win)
    Point(x, y+1).draw(win)
    Point(x+1, y+1).draw(win)

def drawLine(x1,y1,x2,y2):
    x1 = x1*4
    x2 = x2*4
    y1 = y1*4
    y2 = y2*4
    Line(Point(x1,y1), Point(x2,y2)).draw(win)
    Line(Point(x1+1,y1), Point(x2+1,y2)).draw(win)
    Line(Point(x1,y1+1), Point(x2,y2+1)).draw(win)
    Line(Point(x1+1,y1+1), Point(x2+1,y2+1)).draw(win)
    return

def draw_virbes():
    x= 42;
    y= 17;
    prev_offset = 0;
    prev_lenght = 0;
    prev_fpo = 0;
    prev_lpo = 0;
    pows= [16,8,4,2,1];
    j = 0
    for j in range(17):
        lenght = 0;
        off_set = 0;
        row = image[j];
        for i in range(4):
            lenght += bitRead(row,7-i)*pows[i];
        off_set = (-1 if bitRead(row,2) else 1)*(2*bitRead(row,1)+bitRead(row,0))+prev_offset;
        first_point_offset = -1*math.floor(lenght / 2)+off_set;
        drawPixel(x+first_point_offset, y+j);
        last_point_offset = first_point_offset + lenght;
        drawPixel(x+last_point_offset, y+j);
        if (abs(first_point_offset - prev_fpo) >= 2):
            drawLine(x+min(first_point_offset,prev_fpo), y+j, x+max(first_point_offset,prev_fpo), y+j);
        if (abs(last_point_offset - prev_lpo) >= 2):
            drawLine(x+min(last_point_offset,prev_lpo), y+j, x+max(last_point_offset,prev_lpo), y+j);
        prev_offset = off_set;
        prev_lenght = lenght;
        prev_fpo = first_point_offset;
        prev_lpo = last_point_offset;
    drawLine(x+prev_fpo, y+j, x+prev_lpo, y+j);

def redraw():
    writeimg(image)
    draw_virbes()

def on_close():
    master.destroy()
    win.close()
    sys.exit()

def main():
    #gui
    global master
    master = Tk()
    slicer = Scale(master, from_=0, to=31,
            label="Lenght",
            orient=HORIZONTAL)
    slicer.set(23)
    slicer.pack()
    #graphics
    global win
    win = GraphWin("Sprite Visualizator", 336, 192)
    win.setBackground(color_rgb(150, 190, 120))

    redraw();

    master.protocol("WM_DELETE_WINDOW", on_close)
    master.mainloop()

main()
