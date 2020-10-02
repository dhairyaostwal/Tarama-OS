from flask import Flask, render_template, request, jsonify, redirect
from itertools import combinations

app = Flask(__name__)


insideTarama = []
inqueue = []
currentstatus = []
insideTarama1 = []
inqueue1 = []
currentstatus1 = []
t = []
q = []

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
    for i in range(0, len(t)):
        insideTarama1.insert(i, int(t[i]))
    for i in range(0, len(t)):
        currentstatus1.insert(i, insideTarama[i])
    

    result = []
    result.append(insideTarama1)
    result.append(inqueue1)
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
    l = []
    l1 = []
    sumele = []
    waiting = []


    def schedulecheck():

        waitingtime = 0
        bubble(insideTarama, currentstatus)

        

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
                waiting.insert(inqueue1.index(l1[-1][i]), waitingtime)
                inqueue.pop(inqueue.index(l1[-1][i]))

            # result.append({
            #     'waiting': waiting
            # })

            bubble(insideTarama, currentstatus)
            


            l1.clear()
            sumele.clear()
            if(len(inqueue) == 0):
                break  


    schedulecheck()
    result.append(waiting[0])
    result.append(waiting[1])
    result.append(waiting[2])
    result.append(waiting[3])
    result.append(waiting[4])


    return render_template('Report.html', result=result)


if __name__ == '__main__':
    app.run(debug=True)