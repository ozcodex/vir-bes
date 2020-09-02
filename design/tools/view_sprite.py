from graphics import *
from tkinter import *
import math

def get_bit(x, n=5):
    return format(x, 'b').zfill(n)

global data
data = [
        { "length": 5, "offset": 0},
        { "length": 9, "offset": 0},
        { "length": 11, "offset": 0},
        { "length": 13, "offset": 0},
        { "length": 15, "offset": 0},
        { "length": 16, "offset": 1},
        { "length": 17, "offset": 0},
        { "length": 18, "offset": 0},
        { "length": 18, "offset": 0},
        { "length": 18, "offset": 0},
        { "length": 18, "offset": 0},
        { "length": 18, "offset": 0},
        { "length": 19, "offset": 0},
        { "length": 18, "offset": -1},
        { "length": 20, "offset": -1},
        { "length": 20, "offset": -1},
        { "length": 21, "offset": -1},
        { "length": 22, "offset": -1},
        ]

global image
image = []

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
    canvas.create_rectangle(x,y,x+3,y+3,fill="#000")
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
    prev_length = 0;
    prev_fpo = 0;
    prev_lpo = 0;
    pows= [16,8,4,2,1];
    j = 0
    for j in range(17):
        length = 0;
        off_set = 0;
        row = image[j];
        for i in range(4):
            length += bitRead(row,7-i)*pows[i];
        off_set = (-1 if bitRead(row,2) else 1)*(2*bitRead(row,1)+bitRead(row,0))+prev_offset;
        first_point_offset = -1*math.floor(length / 2)+off_set;
        drawPixel(x+first_point_offset, y+j);
        last_point_offset = first_point_offset + length;
        drawPixel(x+last_point_offset, y+j);
        if (abs(first_point_offset - prev_fpo) >= 2):
            drawLine(x+min(first_point_offset,prev_fpo), y+j, x+max(first_point_offset,prev_fpo), y+j);
        if (abs(last_point_offset - prev_lpo) >= 2):
            drawLine(x+min(last_point_offset,prev_lpo), y+j, x+max(last_point_offset,prev_lpo), y+j);
        prev_offset = off_set;
        prev_length = length;
        prev_fpo = first_point_offset;
        prev_lpo = last_point_offset;
    drawLine(x+prev_fpo, y+j, x+prev_lpo, y+j);

def load_data():
    image = []
    for obj in data:
        bstr = get_bit(obj.get("length"))
        bstr += "1" if obj.get("offset") < 0 else "0"
        bstr += get_bit(abs(obj.get("offset")),2)
        image.append(bstr)

def redraw():
    load_data()
    writeimg(image)
    draw_virbes()

def on_close():
    master.destroy()
    win.close()
    sys.exit()

def update():
    line = int(selector.get())
    length = int(slicer.get())
    data[line]["length"] = length
    redraw()

def select(pos):
    length = data[int(pos)].get("length")
    slicer.set(length)
    return

def main():
    #gui
    global master
    master = Tk()

    global canvas
    canvas = Canvas(
            master,
            bg='#78BE96',
            height=192,
            width=336)

    canvas.pack()

    global selector
    selector = Scale(master, from_=0, to=len(image)-1,
            label="Line",
            orient=VERTICAL,
            command=select,
            length=300)
    selector.pack()

    global slicer
    slicer = Scale(master, from_=0, to=31,
            label="Length",
            orient=HORIZONTAL,
            length=400)
    slicer.pack()

    select(0)

    butt = Button( master, text="redraw", command=update )
    butt.pack()
    #graphics
    global win
    win = GraphWin("Sprite Visualizator", 336, 192)
    win.setBackground(color_rgb(150, 190, 120))

    redraw();

    master.protocol("WM_DELETE_WINDOW", on_close)
    master.mainloop()

main()
