import numpy as np
import cv2 
import imutils 
from xml.dom import minidom
import os
import math

def writeXml(filename,x,y,length,direction):

    i=0
    # doc=parse("./customer.xml")
    if not os.path.exists(filename): 
        # 如果文件没有根节点 创建根节点
        doc = minidom.Document()
        dimension = doc.createElement('dimension')
        i=1
    else:
        # 如果有根节点，访问根节点，在根节点下写入参数
        doc = minidom.parse(filename)
        dimension=doc.documentElement
    line=doc.createElement("line")
    dimension.appendChild(line)
    point1 = doc.createElement("startPoint")
    # distance的子节点，属性是xy坐标
    point1.setAttribute("x", str(x[0]))
    point1.setAttribute("y", str(x[1]))
    point2 = doc.createElement("endPoint")
    # distance的子节点，属性是xy坐标
    point2.setAttribute("x", str(y[0]))
    point2.setAttribute("y", str(y[1]))
    line.appendChild(point1)
    line.appendChild(point2)
    line.setAttribute("length",str(length))
    line.setAttribute("direction",str(direction))
    # distance的属性length，代表测量得到的宽度的长度
    doc.appendChild(dimension)
    # filename = "C:\\Users\\gjw\\Desktop\\dimension.xml"
    if i==1:
        f = open(filename, "a")
        doc.writexml(f,indent='',addindent='\t',newl='\n',encoding='utf-8')
        f.close()
    else:
        with open(filename, 'w') as f:
            # 缩进 - 换行 - 编码
            doc.writexml(f,indent='',addindent='\t',newl='\n',encoding='utf-8')

def mathc_img(image, Target, save_path, value=0.9):
    # image是测量的图片的地址，target是模板的地址，
    # save_path是对齐后的图片的输出地址，value是给定的匹配阈值默认0.9
    img_rgb = cv2.imread(image) 
    img_gray = cv2.cvtColor(img_rgb, cv2.COLOR_BGR2GRAY) 
    template = cv2.imread(Target,0) 
    w, h = template.shape[::-1] 
    res = cv2.matchTemplate(img_gray,template,cv2.TM_CCOEFF_NORMED)  
    if max(map(max,res)) <value:
        return 
    loc = np.where( res >= max(map(max,res))) 
    for pt in zip(*loc[::-1]): 
        # cv2.rectangle(img_rgb, pt, (pt[0] + w, pt[1] + h), (0,0,155), 2) 
        img_crop = img_rgb[pt[1]:pt[1] + h, pt[0]:pt[0] + w]
    # cv2.imshow('Detected',img_crop) 
    cv2.imwrite(save_path + "measure.jpg", img_crop)

def edge(filePath,dirPath):

    img = cv2.imread(filePath,0)

    # 腐蚀
    kernel = np.ones((3,3),np.uint8)
    erosion = cv2.erode(img,kernel,iterations = 1)
    cv2.imwrite(dirPath + "erosion.jpg",erosion)# 保存腐蚀后的图片

    # 膨胀
    dilate = cv2.dilate(erosion,kernel,iterations = 1)

    # 显示图片
    # ## 效果展示
    cv2.imwrite(dirPath + "3-6dilate.jpg",dilate)

    #  边缘提取 并保存图片
    canny1=cv2.Canny(dilate,150,200)
    cv2.imwrite(dirPath + "3-6canny.jpg",canny1)

    #  去除孤立点
    _, labels, stats, centroids = cv2.connectedComponentsWithStats(canny1)

    i=0
    for istat in stats:
        if istat[4]<120:
            if istat[3]>istat[4]:
                r=istat[3]
            else:r=istat[4]
            cv2.rectangle(canny1,tuple(istat[0:2]),tuple(istat[0:2]+istat[2:4]) , 0,thickness=-1)  # 26
        i=i+1

    #  保存去除孤立点后的边缘提取图片 并展示
    cv2.imwrite(dirPath + "3-6canny1.jpg",canny1)   
    return

def distanceCalculate(dirPath,Left,Right,direction): #测量上下边界的宽度 传入保存边缘的路径 ROI的左右顶点位置 输出宽度值
    img=cv2.imread(dirPath + "3-6canny1.jpg", flags=cv2.IMREAD_COLOR)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # 选取要测量的部分
    # cv2.namedWindow('Canny Edge', cv2.WINDOW_NORMAL) 
    # bbox = cv2.selectROI('Canny Edge',img ,False)
    cut = img[Left[1]:Right[1], Left[0]:Right[0]]
    ret,cut = cv2.threshold(cut,0,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)    
    img=cut

    distance = 10000
    h, w = img.shape
    line = int(h/2)     #取中间轴
    conture_up=np.zeros(w)       #上方轮廓
    conture_down=np.zeros(w)     #下方轮廓
    for j in range(w):          #找到上部的轮廓
        for i in range(line):
            pv=img[i,j]
            if pv>0:
                conture_up[j] = i
                continue
    for j in range(w):          #找到下部的轮廓
        for i in range(line,h):
            pv=img[i,j]
            if pv>0:
                conture_down[j] = i
                continue
    for j in range(w):             #计算
        for i in range(w):
            d2=(i-j)*(i-j)+(conture_down[j]-conture_up[i])*(conture_down[j]-conture_up[i])
            if np.sqrt(d2)<distance:
                distance=np.sqrt(d2)
                point1=[i+Left[0],conture_up[i]+Left[1]]
                point2=[j+Left[0],conture_down[j]+Left[1]]
     
    writeXml(dirPath + "dimension.xml",point1,point2,distance,direction)
    return

def findLine(path, Left, Right,direction): 
    # 测量边缘提取后的图片的线段长度，
    # 输入边缘提取后的照片路径，测量区域的左上点坐标和右下点坐标 
    # 线段的长度和两个点
    #与v4相比加上了xml文件部分
    point = [] # 点集，用来储存是线段的点的坐标
    img = cv2.imread(path + "3-6canny1.jpg")
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    ret, edges = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY+ cv2.THRESH_OTSU) 
    # 把unit8格式的图片数据二值化
    edges = edges[Left[1]:Right[1], Left[0]:Right[0]]
    # cv2.namedWindow('lines2',cv2.WINDOW_NORMAL)
    # cv2.imshow("lines2", edges)
    img = img[Left[1]:Right[1], Left[0]:Right[0]]
    # 对图像进行裁剪，缩小计算区域，提高精度
    Max = 0 # 用于计算点集中相聚最远的点
    lines = cv2.HoughLines(edges,1,np.pi/180, 20)
    # 霍夫变换提取直线
    for r,theta in lines[0]:
        # Stores the value of cos(theta) in a
        a = np.cos(theta)
        # Stores the value of sin(theta) in b
        b = np.sin(theta)
        # x0 stores the value rcos(theta)
        x0 = a*r
        # y0 stores the value rsin(theta)
        y0 = b*r
        # x1 stores the rounded off value of (rcos(theta)-1000sin(theta))
        x1 = int(x0 + 1000*(-b))
        # y1 stores the rounded off value of (rsin(theta)+1000cos(theta))
        y1 = int(y0 + 1000*(a))
        # x2 stores the rounded off value of (rcos(theta)+1000sin(theta))
        x2 = int(x0 - 1000*(-b))
        #y2 stores the rounded off value of (rsin(theta)-1000cos(theta))
        y2 = int(y0 - 1000*(a))
        # cv2.line draws a line in img from the point(x1,y1) to (x2,y2).
        # (0,0,255) denotes the colour of the line to be 
        #drawn. In this case, it is red. 
        cv2.line(img,(x1,y1), (x2,y2), (0,0,255),1) #把直线用红色画出来，1倍宽度，方便观测，后面主要用(x1,y1)和(x2,y2)两个点计算

    

    for x in range(edges.shape[0]):   # 图片的高
        for y in range(edges.shape[1]):   # 图片的宽
            px = edges[x,y]
            if px == 255: # 如果是边缘点，计算与拟合直线的距离
                if get_point_line_distance([y,x],[[x1,y1],[x2,y2]]) <= 1: #距离小于阈值就加入点集，1是阈值可以随便改

                # if img[x,y][0]==0 and img[x,y][1]==0 and img[x,y][2]==255:
                    img[x,y][1], img[x,y][2] = 255, 0 #标绿方便观察
                    point.append([y+Left[0], x+Left[1]]) #把目标点加入点集
                  
    for i,p in enumerate(point):
        for j in range(i+1,len(point)):
            p2 = point[j]
            d = math.sqrt((p[0] - p2[0]) * (p[0] - p2[0]) + (p[1] - p2[1]) * (p[1] - p2[1])) #计算距离最大的两个点
            if d > Max :
                Max = d
                xx1 = i #保存数据
                xx2 = j
    # cv2.imshow("lines", img)
    # cv2.imwrite('C:\\Users\\93115\\Desktop\\mat\\3-25line.jpg', img)
    # print(count)
    # cv2.waitKey()
    # cv2.destroyAllWindows()
    writeXml(path + "dimension.xml", point[xx1], point[xx2], Max,direction)

def get_point_line_distance(point, line):
    point_x = point[0]
    point_y = point[1]
    line_s_x = line[0][0]
    line_s_y = line[0][1]
    line_e_x = line[1][0]
    line_e_y = line[1][1]
    #若直线与y轴平行，则距离为点的x坐标与直线上任意一点的x坐标差值的绝对值
    if line_e_x - line_s_x == 0:
        return math.fabs(point_x - line_s_x)
    #若直线与x轴平行，则距离为点的y坐标与直线上任意一点的y坐标差值的绝对值
    if line_e_y - line_s_y == 0:
        return math.fabs(point_y - line_s_y)
    #斜率
    k = (line_e_y - line_s_y) / (line_e_x - line_s_x)
    #截距
    b = line_s_y - k * line_s_x
    #带入公式得到距离dis
    dis = math.fabs(k * point_x - point_y + b) / math.pow(k * k + 1, 0.5)
    return dis
    
    