from flask import Flask,request,render_template

app=Flask(__name__)

@app.route('/')
def formpost():
    tex = '一个包含xss漏洞的网页'
    if request.args.get('text'):
        tex = request.args.get('text')
        # print(tex)
    return render_template('show.html',data=tex)

if __name__=='__main__':
    app.run(debug=True)