# 1 实验要求

要实现的预期是：

1.先编写一个html网站页面(含有提交框和显示框)，然后向提交框提交一份代码，在显示框显示。如果是文本就储存在数据库中，直接拿出来显示，如果是恶意代码，就会在浏览器中执行。


2.机器人模拟这个提交代码触发漏洞的过程。


# 2 实验过程

## 2.1 

发布评论，评论要展示在界面上，展示的这个过程，如果是文本则显示文本，如果是js代码，则执行
如何能让文本显示文本，但是同时能执行js代码？

遇到的困难：
* flask jinjia会转义，把js代码变成大写字母，所以无法执行
* 会将js中的alert去掉

* 处理方法：只能在href都可以触发、onclick
* [XSS跨站脚本小结]('https://www.cnblogs.com/xiaozi/p/5588099.html')

```html
javascript:alert('jdlnb!!');
javascript:document.write('<h1>jdlnb!</h1>');
```

## 2.2 

## 跨站脚本漏洞
* 1.[概念]('https://www.jianshu.com/p/4fcb4b411a66')
* 
* [另一个博客的概念解释]('https://www.cnblogs.com/Detector/p/8811216.html')
* [跨站脚本的网站]('https://pentesterlab.com/exercises/xss_and_mysql_file/course')  


* [flask.jinja2模板中自动转义和取消转义的分析]('https://blog.csdn.net/fanny_git/article/details/78072690')

```html
{% autoescape false %}
{% endautoescape %}
```

或者是
```html
{{data|safe}}
```

```html
<strong>揭大佬牛逼</strong>
```