import zbarlight
import os
import sys
import PIL
import time
import mysql.connector
from mysql.connector import Error
from mysql.connector import errorcode
try:
    db = mysql.connector.connect(host='localhost', database='smistamento', user='User', password='Password')
except mysql.connector.Error as error:
    print("Failed".format(error))

while 1:
    print 'Taking picture..'
    try:
        f = 1
        qr_count = len(os.listdir('qr_codes'))
        os.system('sudo fswebcam -d /dev/video0 -q qr_codes/qr_'+str(qr_count)+'.jpg')
        print 'Picture taken..'
    except:
        f = 0
        print 'Picture couldn\'t be taken..'

    print

    if(f):
        info = ""
        print 'Scanning image..'
        f = open('qr_codes/qr_'+str(qr_count)+'.jpg','rb')
        qr = PIL.Image.open(f);
        qr.load()
        codes = zbarlight.scan_codes('qrcode',qr)
        if(codes==None):
            os.remove('qr_codes/qr_'+str(qr_count)+'.jpg')
            print 'No QR code found'
        else:
            print 'QR code(s):'
            f = open('qr_code_messages.txt','a')
            for i in range(len(codes)):
                f.write(codes[i])
                info = info + codes[i]
                if(i!=len(codes)-1):
                    f.write('^')
            f.write('~')
            os.remove('qr_codes/qr_'+str(qr_count)+'.jpg')
            info = info.split("-")
            print info
            cursor = db.cursor()
            cursor.execute("INSERT INTO pacchi (corriere, cap, peso) VALUES (" + info[0] + ",'" + info[1] + "'," + info[2] + ")")
            db.commit()
            print (cursor.rowcount, "Success")
    time.sleep(1.2)
