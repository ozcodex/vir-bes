from graphics import *
from tkinter import *
import json
import math

factor = 6; #more than 2
h = 48;
w = 84

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

def load_sdata():
    global data
    with open(filename.get(), 'r') as f:
        data = json.loads(f.read())
        print(data) 
def save_sdata():
    with open(filename.get(), 'w') as f:
        f.write(json.dumps(data))
        print(data) 

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
    x = x*factor
    y = y*(factor+1)
    canvas.create_rectangle(x,y,x+factor-2,y+factor,fill="#000")

def drawLine(x1,y1,x2,y2):
    x1 = x1*factor
    x2 = x2*factor
    y1 = y1*(factor+1)
    y2 = y2*(factor+1)
    mod = math.ceil(factor/2)
    line = canvas.create_line(x1, y1+mod, x2+factor-1, y2+mod,width=factor+1);
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
    for j in range(18):
        length = 0;
        off_set = 0;
        row = image[j];
        for i in range(5):
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
    drawLine(x+prev_fpo, y+j+1, x+prev_lpo, y+j+1);

def load_data():
    image.clear()
    select(selector.get())
    for obj in data:
        bstr = get_bit(obj.get("length"))
        bstr += "1" if obj.get("offset") < 0 else "0"
        bstr += get_bit(abs(obj.get("offset")),2)
        image.append(bstr)

def draw_grid():
    for i in range(w):
        canvas.create_line(i*factor-1,0,i*factor-1,h*factor,fill="#556B2F")
    for j in range(h):
        canvas.create_line(0,j*(factor+1),w*factor,j*(factor+1),fill="#556B2F")

def draw_guide():
    x= 60
    y = 17+int(selector.get())
    canvas.create_rectangle(x*factor-1,0,84*factor,48*factor,outline="#78BE96",fill='#78BE96')
    draw_grid()
    drawLine(x,y,84,y)
    arrow_len = 2
    drawLine(x,y,x+arrow_len,y-arrow_len)
    drawLine(x,y,x+arrow_len,y+arrow_len)

def redraw():
    canvas.create_rectangle(0,0,w*factor,h*factor,outline="#78BE96",fill='#78BE96')
    draw_guide()
    load_data()
    writeimg(image)
    draw_virbes()

def on_close():
    master.destroy()
    sys.exit()

def update():
    line = int(selector.get())
    length = int(slicer.get())
    offset = int(slider.get())
    data[line]["length"] = length
    data[line]["offset"] = offset
    redraw()

def select(pos):
    draw_guide()
    length = data[int(pos)].get("length")
    offset = data[int(pos)].get("offset")
    slicer.set(length)
    slider.set(offset)
    return

def action_load():
    load_sdata()
    redraw()

def action_save():
    save_sdata()
    redraw()

def main():
    #gui

    global master
    global canvas
    global selector
    global slicer
    global slider
    global filename

    master = Tk()
    canvas = Canvas(
            master,
            height=h*factor,
            width=w*factor)

    selector = Scale(master, from_=0, to=len(data)-1,
            orient=VERTICAL,
            command=select,
            length=300)

    slicer = Scale(master, from_=0, to=31,
            label="Length",
            orient=HORIZONTAL,
            length=400)
    
    slider = Scale(master, from_=-3, to=3,
            label="Offset",
            orient=HORIZONTAL,
            length=100)

    separ1 = Label(master)
    butt1 = Button( master, text="redraw", command=update )
    etiq1 = Label( master, text="File name:")
    filename = Entry( master)
    butt2 = Button( master, text="load", command=action_load )
    butt3 = Button( master, text="save", command=action_save )

    canvas.grid(column=0, row=0, columnspan=3)
    selector.grid(column=3, row=0) #row
    slicer.grid(column=0, row=1, columnspan=2) #lenght
    slider.grid(column=2, row=1) #offset
    butt1.grid(column=3, row=1)
    separ1.grid(column=0, row=2)
    etiq1.grid(column=0, row=5)
    filename.grid(column=1, row=5)
    butt2.grid(column=2, row=5)
    butt3.grid(column=3, row=5)

    filename.insert(0,"data.json")
    filename.focus_set()

    select(0)
    redraw();

    master.protocol("WM_DELETE_WINDOW", on_close)
    master.mainloop()

main()
