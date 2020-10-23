from flask import Flask, render_template, request, jsonify, redirect
from itertools import combinations
from reportlab.pdfgen import canvas

app = Flask(__name__)


insideTarama = []
inqueue = []
currentstatus = []
insideTarama1 = []
inqueue1 = []
inqueue2 = []
currentstatus1 = []
t = []
q = []
result = []


@app.route('/')
def index():
    return render_template('home.html')

@app.route('/fillinsidetarama', methods = ['GET', 'POST'])
def hello():
    insideTarama.clear()
    currentstatus.clear()
    if(request.method == 'POST'):
        t.append(request.form.get("zero"))
        t.append(request.form.get("one"))
        t.append(request.form.get("two"))
        t.append(request.form.get("three"))
        t.append(request.form.get("four"))
        return redirect('/fillinqueue')
    return render_template('TaramaVacant.html')


@app.route('/fillinqueue', methods = ['GET', 'POST'])
def fill():
    inqueue.clear()
    if(request.method == 'POST'):
        q.append(request.form.get("zero"))
        q.append(request.form.get("one"))
        q.append(request.form.get("two"))
        q.append(request.form.get("three"))
        q.append(request.form.get("four"))
        q.append(request.form.get("five"))
        return redirect('/answers')
    return render_template('TaramaWaiting.html')

@app.route('/answers')
def display():
    for i in range(0, len(q)):
        inqueue.insert(i, int(q[i]))
    for i in range(0, len(t)):
        insideTarama.insert(i, int(t[i]))
    for i in range(0, len(t)):
        currentstatus.insert(i, insideTarama[i])

    for i in range(0, len(q)):
        inqueue1.insert(i, int(q[i]))
    for i in range(0, len(q)):
        inqueue2.insert(i, int(q[i]))
    for i in range(0, len(t)):
        insideTarama1.insert(i, int(t[i]))
    for i in range(0, len(t)):
        currentstatus1.insert(i, insideTarama[i])
    

    result.append(insideTarama1)
    result.append(inqueue2)
    def unique(list1): 
        list_set = set(list1) 
        unique_list = (list(list_set)) 
        return unique_list

    def mini(arr):
        for i in range(0, len(arr)):
            if(arr[i] != 0):
                return arr[i]

    def minii(arr):
        for i in range(0, len(arr)):
            if(arr[i] != -1):
                return arr[i]

    def bubble(arr, b):
        n = len(arr) 

        for i in range(n-1): 
            for j in range(0, n-i-1): 
                if arr[j] > arr[j+1] : 
                    arr[j], arr[j+1] = arr[j+1], arr[j] 
                    b[j], b[j+1] = b[j+1], b[j] 

    capacity = 30
    replacedpos = []
    l1 = []
    sumele = []
    waiting = []
    for i in inqueue1:
        waiting.append(i)


    def schedulecheck():

        waitingtime = 0
        bubble(insideTarama, currentstatus)
        bubble(inqueue, waiting)

        

        Vacancy = capacity - sum(insideTarama)
        

        while(True):
            bubble(insideTarama, currentstatus)


            temp = 0
            for i in range(0, len(inqueue)):
                if(Vacancy < minii(inqueue) or Vacancy == 0):
                    temp = mini(currentstatus)
                    waitingtime += temp
                    for j in range(0, len(insideTarama)):
                        if(currentstatus[j] >= temp):
                            currentstatus[j] -= temp
                        else:
                            currentstatus[j] = 0
                    for j in range(0, len(currentstatus)):
                        if(currentstatus[j] == 0):
                            Vacancy += insideTarama[j]
                            insideTarama[j] = 0
                            replacedpos.append(j)
                else:
                    break
            for i in range(len(inqueue), 0, -1):
                comb = combinations(inqueue, i)
                for j in comb:
                    if(sum(j) <= Vacancy):
                        l1.append(j)
                        sumele.append(sum(j))

            bubble(sumele, l1)


            Vacancy -= sumele[len(sumele) - 1]
            insideTarama.extend(list(l1[len(l1) - 1]))
            currentstatus.extend(list(l1[len(l1) - 1]))

            for i in range(0, len(unique(replacedpos))):
                unique(replacedpos)[i] -= i
                insideTarama.pop(unique(replacedpos)[i] - i)
                currentstatus.pop(unique(replacedpos)[i] - i)

            replacedpos.clear()


            for i in range(0, len(l1[-1])):
                waiting[inqueue1.index(l1[-1][i])] = waitingtime
                inqueue.pop(inqueue.index(l1[-1][i]))
                inqueue1[inqueue1.index(l1[-1][i])] = 0

            bubble(insideTarama, currentstatus)
            


            l1.clear()
            sumele.clear()
            if(len(inqueue) == 0):
                break  


    schedulecheck()

    for i in waiting:
        result.append(i)

    result.append(max(waiting))
    result.append(max(waiting) / len(inqueue1))

    return render_template('Report.html', result=result)
@app.route('/report')
def generatepdf():
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
    fileName = 'report.pdf'
    documentTitle = 'Waiting Time Report'
    title = 'TaramaOS'
    subtitle = 'We are sorry to keep you waiting :('

    textlines=['Group 0     =      ','Group 1     =      ','Group 2     =      ','Group 3     =      ','Group 4     =      ']

    pdf = canvas.Canvas(fileName)
    pdf.setTitle(documentTitle)

    pdf.drawString(270,770,title)
    pdf.drawString(210,750,subtitle)


    pdf.drawString(200,690,textlines[0])
    pdf.drawString(300,690,str(result[2]))

    pdf.drawString(200,665,textlines[1])
    pdf.drawString(300,665,str(result[3]))

    pdf.drawString(200,640,textlines[2])
    pdf.drawString(300,640,str(result[4]))

    pdf.drawString(200,615,textlines[3])
    pdf.drawString(300,615,str(result[5]))

    pdf.drawString(200,590,textlines[4])
    pdf.drawString(300,590,str(result[6]))

    pdf.drawString(200,565,textlines[4])
    pdf.drawString(300,565,str(result[7]))

    pdf.drawString(200,540,'Total Waiting Time = ')
    pdf.drawString(320,540,str(result[8]))

    pdf.drawString(200,515,'Average Waiting Time = ')
    pdf.drawString(330,515,str(result[9]))

    drawMyRuler(pdf)

    pdf.save()
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
