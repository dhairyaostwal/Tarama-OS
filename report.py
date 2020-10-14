# Refering this https://www.youtube.com/watch?v=ZDR7-iSuwkQ


def drawMyRuler(pdf):
    pdf.drawString(100,810, 'x100')
    pdf.drawString(200,810, 'x200')
    pdf.drawString(300,810, 'x300')
    pdf.drawString(400,810, 'x400')
    pdf.drawString(500,810, 'x500')
    pdf.drawString(600,810, 'x600')

    pdf.drawString(10,100, 'y100')
    pdf.drawString(10,200, 'y200')
    pdf.drawString(10,300, 'y300')
    pdf.drawString(10,400, 'y400')
    pdf.drawString(10,500, 'y500')
    pdf.drawString(10,600, 'y600')
    pdf.drawString(10,700, 'y700')
    pdf.drawString(10,800, 'y800')


from reportlab.pdfgen import canvas
fileName = 'WaitingReport.pdf'
documentTitle = 'Waiting Time Report'
title = 'TaramaOS'
subtitle = 'We are sorry to keep you waiting :('

textlines=[]


pdf = canvas.Canvas(fileName)
pdf.setTitle(documentTitle)

pdf.drawString(270,770,title)
pdf.drawString(210,750,subtitle)
drawMyRuler(pdf)

pdf.save()
