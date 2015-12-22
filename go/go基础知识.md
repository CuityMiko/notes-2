##不可变字符串
<pre>
package main 
import "fmt"
func main() {
	cat := "cat is cat"
	var rr byte =cat[0]
	fmt.Println(string(rr))
	cat = "dog is not dog"
	fmt.Println(cat)
}

Output==>
c
dog is not dog
</pre>
字符串的不可变性，不允许修改字符串内容。很多初学者可能认为cat = "dog is not dog"不是改变字符串内容了吗？这种理解是错误的，它只是将变量cat指向了另一个内存地址，原来字符串并没改变，你改变的只是变量的地址。
在Go语言中，单引号表示一个Unicode字符。
<pre>
package main 
import "fmt"
func main() {
	var m [5]byte = [5]byte{}
	m[0] = 'c'
	fmt.Println(m)
}

Output==>
[99 0 0 0 0]
</pre>
这里使用长度为5的字节数组来存放，并且在第一个位置放入‘c’字符，99就对应了'c'字符的ascii码值。最后打印结果,效果如上。对于中文的编码需要3个字节。而该byte类型的数组，每个数组元素只有一个字节容量，所以放不下中文字符，那么如果我们非要放中文字符。解决方法是：
<pre>
package main 
import "fmt"
func main() {
	var m [5]rune=[5]rune{}
	m[0] = 'c'
	m[1] = '猫'
	fmt.Println(m)
}
Output==>
[99 29483 0 0 0]
</pre>
将byte数组换成rune类型的数组就行了。原因就是rune是有32位的长度，足够放下3个字节表示的中文字符了 。<br>
连接跨行行字符串时，"+" 必须在上⼀一⾏行末尾，否则导致编译错误。
<pre>
s := "hello" + 
"world"
</pre>
##字符串遍历
这里有两种情况：
<br>下面一种是纯英文格式，比较方便。
<pre>
package main 
import "fmt"
func main() {
	a := "my name is jason"
	for i:=0; i< len(a);i++{
		fmt.Printf("%c",a[i])
	}
}
Output==>
my name is jason
</pre>
%c表示格式化成字符.
<br>第二种是带有中文的。
<pre>
package main 
import "fmt"
func main() {
	a := "我是谁"
	b := []rune(a)
	for i:=0;i< len(b);i++{
		fmt.Printf("%c",b[i])
	}
}
</pre>
把字符串里面的byte数组转成rune数组就可以了.
##字符串拼接
直接用+就行了。
<pre>
package main
import "fmt"
func main() {
	a := "你"
	b := a + "好"
	fmt.Println(b)
}
Output==>
你好
</pre>
如果想提高性能，可以导入bytes包，如下：
<pre>
package main
import (
	"fmt"
	"bytes"
)
func main (){
	a := bytes.Buffer{}
	a.WriteString("你")
	a.WriteString("好")
	fmt.Println(a.String())
}
Output==>
你好
</pre>
##给定一个int型数组，找出其中的奇数
<pre>
package main
import "fmt"
func main (){
	arr := []int{1,3,-5,41,22,64}
	for _,num := range arr {
		if isOdd(num) {
			fmt.Printf("%d\n",num)
		}
	}
}
func isOdd(num int) bool {
	return num & 1 == 1
}
Output==>
1
3
-5
41
</pre>

###GO语言range的用法
range是go语言系统定义的一个函数。
函数的含义是在一个数组中遍历每一个值，返回该值的下标值和此处的实际值。
假如说a[0]=10，则遍历到a[0]的时候返回值为0，10两个值。
range关键字用于循环遍历数组，切片，管道或映射项目。数组和切片，它返回项目作为整数的索引。映射返回下一个键 - 值对的键。无论是范围返回一个或两个值。
<pre>
package main
import (
	"fmt"
)
func main (){
	sum := 0.0
	var avg float64
	xs := []float64 {1,2,3,4,5,6}
	switch len(xs) {
		case 0:
			avg =0
		default:
		for _,v := range xs {
			sum += v
		}
		avg = sum /float64(len(xs))
	}
	fmt.Println(avg)
}

Output ==>
3.5
</pre>

<pre>
package main
import "fmt"
func main {
   /* create a slice */
   numbers := []int{0,1,2,3,4,5,6,7,8} 
   /* print the numbers */
   for i:= range numbers {
      fmt.Println("Slice item",i,"is",numbers[i])
   } 
   /* create a map*/
   coutryCapitalMap := map[string] string {"France":"Paris","Italy":"Rome","Japan":"Tokyo"}
   /* print map using keys*/
   for country := range countryCapitalMap {
      fmt.Println("Capital of",country,"is",countryCapitalMap[country])
   }
   /* print map using key-value*/
   for country,capital := range countryCapitalMap {
      fmt.Println("Capital of",country,"is",capital)
   }
}
output ==>
Slice item 0 is 0
Slice item 1 is 1
Slice item 2 is 2
Slice item 3 is 3
Slice item 4 is 4
Slice item 5 is 5
Slice item 6 is 6
Slice item 7 is 7
Slice item 8 is 8
Capital of France is Paris
Capital of Italy is Rome
Capital of Japan is Tokyo
Capital of France is Paris
Capital of Italy is Rome
Capital of Japan is Tokyo
</pre>


###go二维数组
<pre>
package main
import "fmt"
func main (){
	var two [2][3]int
	for i:=0;i<2;i++{
		for j:= 0; j< 3; j++{
			two[i][j] =i + j
		}
	}
	fmt.Println("2d:",two)
}

Output ==>
2d: [[0 1 2] [1 2 3]]
</pre>

<pre>
package main
import "fmt"
func main() {
    //跟数组（arrays）不同，slices的类型跟所包含的元素类型一致（不是元素的数量）。使用内置的make命令，构建一个非零的长度的空slice对象。这里我们创建了一个包含了3个字符的字符串 。(初始化为零值zero-valued)
    s := make([]string, 3)
    fmt.Println("emp:", s)
    //我们可以像数组一样进行设置和读取操作。
    s[0] = "a"
    s[1] = "b"
    s[2] = "c"
    fmt.Println("set:", s)
    fmt.Println("get:", s[2])
    //获取到的长度就是当时设置的长度。
    fmt.Println("len:", len(s))
    //相对于这些基本的操作，slices支持一些更加复杂的功能。有一个就是内置的append，可以在现有的slice对象上添加一个或多个值。注意要对返回的append对象重新赋值，以获取最新的添加了元素的slice对象。
    s = append(s, "d")
    s = append(s, "e", "f")
    fmt.Println("apd:", s)
    //Slices也可以被复制。这里我们将s复制到了c，长度一致。
    c := make([]string, len(s))
    copy(c, s)
    fmt.Println("cpy:", c)
</pre>
<b>slices跟arrays是两种不同的数据类型，但是他们的fmt.Println打印方式很相似。</b>


###Slices：切片
Slices是Go语言中的关键数据类型，它有比数组（arrays）更强的访问接口。
Go编程切片是一种抽象了Go编程数组。由于Go编程数组允许您定义的变量，可容纳同类的几个数据项类型，但它不提供任何内置的方法来动态地增加它的大小或得到一个子数组自身。切片覆盖这一限制。它提供了数组所需的多种效用函数，被广泛应用在Go编程。
####定义切片
要定义一个切片，你可以声明它作为一个数组时，不需要指定大小或使用make函数来创建。
<pre>
var numbers []int /* a slice of unspecified size */
/* numbers == []int{0,0,0,0,0}*/
numbers = make([]int,5,5) /* a slice of length 5 and capacity 5*/
</pre>
####len() 和 cap() 函数
由于切片是一种抽象数组。它实际上使用数组作为底层structure.len()函数返回的元素呈现在cap()函数返回切片作为多少元素，它可以容纳的容量的切片。以下为例子来解释片的使用：
<pre>
package main
import "fmt"
func main {
   var numbers = make([]int,3,5)
   printSlice(numbers)
}
func printSlice(x []int){
   fmt.printf("len=%d cap=%d slice=%v\n",len(x),cap(x),x)
}
output ==>
len=3 cap=5 slice=[0 0 0]
</pre>
####Nil 切片
如果一个切片，没有输入默认声明，它被初始化为为nil。其长度和容量都为零。
<pre>
package main

import "fmt"

func main {
   var numbers []int
   
   printSlice(numbers)
   
   if(numbers == nil){
      fmt.printf("slice is nil")
   }
}

func printSlice(x []int){
   fmt.printf("len=%d cap=%d slice=%v\n",len(x),cap(x),x)
}
output ==>
len=0 cap=0 slice=[]
slice is nil
</pre>
####append() 和 copy() 函数
Slice允许增加使用切片的append()函数。使用copy()函数，源切片的内容复制到目标切片。下面是一个例子：
<pre>
package main

import "fmt"

func main {
   var numbers []int
   printSlice(numbers)
   
   /* append allows nil slice */
   numbers = append(numbers, 0)
   printSlice(numbers)
   
   /* add one element to slice*/
   numbers = append(numbers, 1)
   printSlice(numbers)
   
   /* add more than one element at a time*/
   numbers = append(numbers, 2,3,4)
   printSlice(numbers)
   
   /* create a slice numbers1 with double the capacity of earlier slice*/
   numbers1 := make([]int, len(numbers), (cap(numbers))*2)
   
   /* copy content of numbers to numbers1 */
   copy(numbers1,numbers)
   printSlice(numbers1)   
}

func printSlice(x []int){
   fmt.printf("len=%d cap=%d slice=%v\n",len(x),cap(x),x)
}

output ==>
len=0 cap=0 slice=[]
len=1 cap=2 slice=[0]
len=2 cap=2 slice=[0 1]
len=5 cap=8 slice=[0 1 2 3 4]
len=5 cap=16 slice=[0 1 2 3 4]
</pre>


###Maps：键值对
Maps是Go语言中的关联数据类型（在其它语言中有时会被称之为哈希表[hashes]或字典[dicts]）
<pre>
package main
import "fmt"
func main (){
	m := make(map[string]int)
	m["k1"]=7
	m["k2"]=13
	fmt.Println(m)
}
Output==>
map[k1:7 k2:13]
</pre>
###引用类型
引用类型包括slice、map、channel,他们有复杂的内部结构，除了申请内存外，还需要初始化相关属性。<br>
内置函数new计算类型大小，为其分配零值内存。返回指针。而make会被编译器翻译成具体的创建函数，而其分配内存和初始化成员结构，返回对象而不是指针。
##枚举
<pre>
package main
import "fmt"

const (
	sunday =iota
	monday
	tuesdy
	wednesday
	thurday
	friday
	saturday
)
func main (){
	fmt.Println(friday)
}

Output ==>
5
</pre>
Go语言中通过关键字const来定义枚举，上面的例子中，定义了一个关于星期的枚举，当打印Friday时候输出5。打印Sunday输出0。其实，在Go语言中，枚举似乎就是常量一种特殊形式，只不过在上述代码中出现了关键字<b>iota</b>，这个是一个非常有用的东西，可以帮你省写很多东西，在上面他会初始化为0，然后每一行就会增加1，因此可以认为是一个自增量。于是我们就不必这样写了：Sunday=1   Monday=2……一个iota帮你解决一切烦恼，而且在后续中还能对iota进行操作：例如可以Monday = iota*2于是Monday就等于2了。上面说到一行定义一个iota会自增赋值给常量，那么可以一行定义多个吗？答案是可以，但是必须得明确指定值，不然会报错：
<pre>
package main
import "fmt"

const (
	sunday =iota
	monday =iota*2
	tuesday
	wednesday
	thurday
	friday,satuday=15,16
)
func main (){
	fmt.Println(satuday)
}
Output ==>
16
</pre>
发现上面枚举的值都是整数，当然其它类型的也可以，只要相应的赋值就行了，如Sunday = "sun"。

##结构体
Go语言之结构体定义：
结构体，对于学过C语言的应该很熟悉，对于C这样的语言，没有类的概念，结构体在很大程度上是作为封装的主要方式，那么在Go语言中。结构体又是如何的呢？
<pre>
package main
import "fmt"
type Student struct {
	Name string
	age int
}
func main () {
	// var st Student =Student {"tom",18}  st :=Student {"tom" 18}
	st.Name ="cat"
	fmt.Printf("%s %d",st.Name ,st.age)
}
Output ==>
cat 18
</pre>
发现和c语言差不多么，如果仔细看你会发现结构体中的Name首字母N是大写的，而age的首字母a是小写的。这可不是随便的哦。虽然这里我是随便的。<b>在Go语言中如果结构的Field首字母大写，那么它是public的，可以在package外访问。而age首字母是小写的，那么它只能在本package中被访问。</b>是否和java中类的字段用private关键字或者public定义类似呢？
上述代码中我们声明并初始化st变量是一起进行的，当然也可以分开：
<pre>
if err != nil {
	return err
}

if err !=nil{
 panic(err)
}
</pre>
###cap()函数
cap()函数返回的是数组切片分配的空间大小。
<pre>
package main
import "fmt"
func main(){
	myslice := make([]int,5,10)
	fmt.Println("len(myslice):",len(myslice))
	fmt.Println("cap(myslice):",cap(myslice))
}

Output==>
len(myslice):5
cap(myslice):10
</pre>
###unsafe
由于Go语言不能和C语言一样直接进行指针运算，所以需要引入unsafe包，通过它进行运算.unsafe.Pointer其实就是类似C的void *，在golang中是用于各种指针相互转换的桥梁。
在Go语言中，指针的本质是什么呢？是unsafe.Pointer和uintptr。

##import详解
我们在写Go代码的时候经常用到import这个命令用来导入包文件，而我们经常看到的方式参考如下：
<pre>
 import(
    "fmt"
)
</pre>
然后我们代码里面可以通过如下的方式调用
<pre>
 fmt.Println("hello world")
</pre>
上面这个fmt是Go语言的标准库，其实是去GOROOT环境变量指定目录下去加载该模块，当然Go的import还支持如下两种方式来加载自己写的模块：

* 相对路径
<pre>
import “./model” //当前文件同一目录的model目录，但是不建议这种方式来import
</pre>
* 绝对路径
<pre>
import “shorturl/model”//加载gopath/src/shorturl/model模块
</pre>
上面展示了一些import常用的几种方式，但是还有一些特殊的import，让很多新手很费解，下面我们来一一讲解一下到底是怎么一回事

* 点操作<br>
我们有时候会看到如下的方式导入包
<pre>
 import(
    . "fmt"
)
</pre>
这个点操作的含义就是这个包导入之后在你调用这个包的函数时，你可以省略前缀的包名，也就是前面你调用的fmt.Println("helloworld")可以省略的写成Println("helloworld")

* 别名操作<br>
别名操作顾名思义我们可以把包命名成另一个我们用起来容易记忆的名字
<pre>
 import(
    f "fmt"
)
</pre>
别名操作的话调用包函数时前缀变成了我们的前缀，即f.Println("helloworld")

*  _ 操作<br>
这个操作经常是让很多人费解的一个操作符，请看下面这个import
<pre>
 import (
    "database/sql"
    _ "github.com/ziutek/mymysql/godrv"
)
</pre>
_操作其实是引入该包，而不直接使用包里面的函数，而是调用了该包里面的init函数。
###基础知识
- %d 十进制整形
- %ld 十进制长整形
- %s 字符串
- %c 字符型
- %f 浮点型

###方法
一般我们把类的成员函数叫做Methods（方法）。
<pre>
package main
import "fmt"
type mystring string
func (str mystring) prefix(preStr string)(newStr mystring){
	newStr =mystring(preStr) + str
	return
}

func main (){
	var before mystring ="go"
	after := before.prefix("let`s")
	fmt.Printf("%s\n",before)
	fmt.Printf("%s\n",after)
}

Ouptut ==>
go
let`s go
</pre>
面的程序中，第4行我们定义了一种新类型mystring，其实就是string的别名。当然，你可以定义你想要的类型，比如上篇中的结构体。

<pre>
package main
import "fmt"
type Person struct {
	name string
	age int8
}
func (p Person)getName()string {
	return p.name
}
func main (){
	p:=Person{"slick",21}
	fmt.Printf("%s \n",p.getName())
	p.name="gogo"
	fmt.Printf("%s\n",p.getName())
}

Output ==>
slick 
gogo
</pre>

###GO中的接口
最基本的接口形式：
<pre>
type show interface {
	draw()
	count()
}
</pre>
和定义一个结构体类似，只不过将struct换成了interface，然后声明了两个函数：draw()和count()。就这么简单，一个接口就定义好了，那么如何实现接口呢？
<pre>
package main
import (
    "fmt"
)
 
type Sorter interface {
    Len() int
    Less(i, j int) bool
    Swap(i, j int)
}
 
type Xi []int
type Xs []string
 
func (p Xi) Len() int { return len(p) }
func (p Xi) Less(i int, j int) bool { return p[j] < p[i] }
func (p Xi) Swap(i int, j int) { p[i], p[j] = p[j], p[i] }
 
func (p Xs) Len() int { return len(p) }
func (p Xs) Less(i int, j int) bool { return p[j] < p[i] }
func (p Xs) Swap(i int, j int) { p[i], p[j] = p[j], p[i] }
 
 
func Sort(x Sorter) {
    for i := 0; i < x.Len() - 1; i++ {
        for j := i + 1; j < x.Len(); j++ {
            if x.Less(i, j) {
                x.Swap(i, j)
            }
        }
    }
}
func main() {
    ints := Xi{44, 67, 3, 17, 89, 10, 73, 9, 14, 8}
    strings := Xs{"nut", "ape", "elephant", "zoo", "go"}
    Sort(ints)
    fmt.Printf("%v\n", ints)
    Sort(strings)
    fmt.Printf("%v\n", strings)
}

Output ==>
[3 8 9 10 14 17 44 67 73 89]
[ape element go nut zoo]
</pre>

##函数
<pre>
package main
import "fmt"
func say(str string,args... interface {}) (int,error){
	_,err := fmt.Printf(str,args...)
	return len(args),err
}
func main(){
	count := 1
	closure := func (msg string) {
		say("%d %s\n",count,msg)
		count++
	}
	closure("Say one")
	closure("Say again")
}

Output ==>
Say one
Say again
</pre>
 在上述的代码中，我们一共声明并定义了两个函数，一个是say，另一个则是一个匿名函数，而且这里通过匿名函数，生成了一个函数闭包。在Go语言中

使用func关键字声明一个函数。因此，如果你要声明一个函数，马上要想到func，不管是不是匿名函数，唯一的区别就是匿名函数后面没有函数名称了，直接

func（参数列表）（返回值）。从上面我们也看到了，Go语言函数的返回类型在函数名的后面，和它声明变量的类型一样，这也与大部分语言不同的。而且函数的返回值可以是一个，也可以多个。比如上面的say函数，我们就返回了两个，一个整数类型，一个error。其中整数类型的是可变参数的长度，error类型则是从fmt包中Printf函数返回的值中的其中一个，而且我们看到接受fmt.Printf()函数返回值的第一个变量我们使用了"_"符号，这个代表我们不关心第一个返回值，将它忽略。接下来再来看say函数的第二个参数，是一个...interface{}类型，三个点是Go语言的一种类型Slices，类似数组，但是有所不同，这个将在后续文章中继续介绍，既然是一个类似数组的类型，当然也可以想到可变参数可以接收任意多个，但是必须是相同类型的，而这里使用一个空接口类型作为Slices的元素类型，使得可以接收任意类型参数的元素，之后可以通过缺省参数推断出每一个元素真实的类型。
##go的变量类型变换
Go不支持隐式转换，必须手动指明。比如：
<pre>
var a int =2
var b float64=float64(a)
</pre>
##nil 错误
golang的nil在概念上和其它语言的null、None、nil、NULL一样，都指代零值或空值。nil是预先说明的标识符，
也即通常意义上的关键字。在golang中，nil只能赋值给指针、channel、func、interface、map或slice类型的变量。
如果未遵循这个规则，则会引发panic。
<pre>
package main
import "fmt"
func main(){
    var a int
    var b float32
    var c bool====
    var d string
    var e []int
    var f map[string] int
    var g *int
    if nil == e{
        fmt.Print("e is nil \n")
    }
    if nil == f{
        fmt.Print("f is nil \n")
    }
    fmt.Print(a,b,c,d,e,f,g)
}
</pre>
##自动类型转换
<pre>
package main
import "fmt"
func main(){
	var b string
	b="Hello world"
	fmt.Print(b)
}
</pre>
上面的相当于：
<pre>
package main
import "fmt"
func main(){
	b := "Hello world"
	fmt.Print(b)
}
</pre>
go语言编译器自动会推断变量b的类型。

##Go中字符编码问题导致的len问题
Go中默认是UTF-8。
<pre>
package main
import "fmt"
func main () {
	a := "fffs"
	fmt.Println(a)
	fmt.Printf("%d\n",len(a))
}
Output==>
fffs
4
</pre>
###一个疑问： 
当一个字符串中既有英文又有中文时，会出现字符编码错误提示，待解决。


###指针
####什么是指针？
指针是一个变量，其值是另一个变量的地址，所述存储器位置，即，直接地址。就像变量或常量，必须声明指针之前，可以用它来存储任何变量的地址。指针变量声明的一般形式是：
<pre>
var var_name *var-type
</pre>
####如何使用指针？
有一些重要的操作，我们使用指针非常频繁。 （a）定义一个指针变量（b）分配一个变量的指针；（c）在指针变量的地址，可用地址来访问它的值。这可通过使用一元运算符 * ，返回位于其操作数所指定的地址的变量的值。
####在Go中的nil指针
Go语言编译一个 nil 值赋给一个没有被确切的地址分配的指针变量。这样做是在变量声明时，分配 nil 指针被称为nil指针。
<pre>
package main
import "fmt"
func main() {
   var  ptr *int
   fmt.Printf("The value of ptr is : %x\n", ptr  )
}
output ==>
The value of ptr is 0
</pre>
支持指针类型 *T，指针的指针 **T，以及包含包名前缀的  *<package>.T。

- 默认值，没有 NULL 常量。
- 操作符 "&" 取变量地址，"*" 透过指针访问目标对象。
- 不⽀支持指针运算，不⽀支持 "->" 运算符，直接用 "." 访问目标成员。
<pre>
package main
import "fmt"
func main (){
	type data struct {a int}
	var d= data{1234}
	var p *data
	p =&d
	fmt.Printf("%p,%v\n",p,p.a)
}
Output ==>
0x08020022f0,1234
</pre>
<br>格式控制符“%p”中的p是pointer（指针）的缩写.
<br>最简单的方法是用"%v"标志，它可以以适当的格式输出任意的类型（包括数组和结构）。下面是解释%v的乱入程序.<br>
//start
<pre>
package main
import "fmt"
 type T struct {
         a int
         b string
}
func main(){
        t := T{77, "Sunset Strip"}
        a := []int{1, 2, 3, 4}
        fmt.Printf("%v %v %v\n", u64, t, a)
}
Output ==>
 18446744073709551615 {77 Sunset Strip} [1 2 3 4]
</pre>
如果是使用"Print"或"Println"函数的话，甚至不需要格式化字符串。这些函数会针对数据类型 自动作转换。"Print"函数默认将每个参数以"%v"格式输出，"Println"函数则是在"Print"函数 的输出基础上增加一个换行。一下两种输出方式和前面的输出结果是一致的。
<pre>
 fmt.Print(u64, " ", t, " ", a, "\n")
 fmt.Println(u64, t, a)
</pre>

//end
#####不能对指针做加减法等运算。
下面的这个是错误的：
<pre>
x := 1234
p := &x
p++  //Error :不能对指针进行运算
</pre>
那么，怎么对指针进行运算操作呢？将 Pointer 转换成 uintptr，可变相实现指针运算。
<pre>
package main
import "fmt"
import "unsafe"
func main() {
	d := struct {
	s string
	x int
	}{"abc", 100}
	p := uintptr(unsafe.Pointer(&d)) /*  *struct -> Pointer -> uintptr  */
	p += unsafe.Offsetof(d.x) /* uintptr + offset */
	p2 := unsafe.Pointer(p) /* uintptr -> Pointer  */
	px := (*int)(p2) /* Pointer -> *int  */
	*px = 200   //d.x = 200
	fmt.Printf("%#v\n", d)
}

Output ==>
struct {s string; x int}{s:"abc",x:200}
</pre>
####注意：GC 把 uintptr 当成普通整数对象，它⽆无法阻⽌止 "关联" 对象被回收。
###Go语言指针数组
<pre>
package main
import "fmt"
const MAX int = 3
func main() {
   a := []int{10,100,200}
   var i int
   for i = 0; i < MAX; i++ {
      fmt.Printf("Value of a[%d] = %d\n", i, a[i] )
   }
}

output ==>
Value of a[0] = 10
Value of a[1] = 100
Value of a2] = 200
</pre>
##感悟
###Channel与锁谁轻量
Channel和锁谁轻量? 一句话告诉你: Channel本身用锁实现的. 因此在迫不得已时, 还是尽量减少使用Channel, 但Channel属于语言层支持, 适度使用, 可以改善代码可读写
###设计
踏入Golang, 就不要尝试设计模式
传统的OO在这里是非法的, 尝试模拟只是一种搞笑
把OO在Golang里换成复合+接口
对实现者来说, 把各种结构都复合起来, 对外暴露出一个或多个接口, 接口就好像使用者在实现模型上打出的很多洞
别怕全局函数, 包(Package)可以控制全局函数使用范围.
没必要什么都用interface对外封装, struct也是一种良好的封装方法
Golang无继承, 因此无需类派生图. 没有派生这种点对点的依赖, 因此不会在大量类关系到来时, 形成繁杂不可变化的树形结构
###容器
用了很长时间map, 才发现Golang把map内建为语言特性时, 已经去掉了外置型map的api特性. 一切的访问和获取都是按照语言特性来做的, 原子化
数组可以理解为底层对象, 你平时用的都是切片, 不是数组, 切片就是指针, 指向数组. 切片是轻量的, 即便值拷贝也是低损耗的
###内存
Golang在实际运行中, 你会发现内存可能会疯涨. 但跑上一段时间后, 就保持稳定. 这和Golang的内存分配, 垃圾回收有一定的关系
现代的编程语言的内存管理不会很粗暴的直接从OS那边分配很多内存. 而是按需的不断分配成块的内存.
对于非海量级应用, Golang本身的内存模型完全可以撑得下来. 无需像C++一样, 每个工程必做内存池和线程池
###错误
觉得Golang不停的处理err? 那是因为平时在其他语言根本没处理过错误, 要不然就是根部一次性try过所有的异常, 这是一种危险的行为
panic可以被捕获, 因此编写服务器时, 可以做到不挂
###危险的interface{}
这东西就跟C/C++里的void*一样的危险, nil被interface{}包裹后不会等于nil相等, 但print出来确实是nil
模板估计可以解决容器内带interface{}的问题. 但新东西引入, 估计又会让现在的哲学一些凌乱
###初学Tips
语言学习按照官网的教学走, 跑完基本就会了
下载一个LiteIDE, 配合Golang的Runtime,基本开环境就有了
Golang的类库设计方式和C#/C++都不同, 如果有Python经验的会感觉毫无违和感
有一万个理由造轮子都请住手, 类库里有你要的东西
写大工程请搜索: Golang项目目录结构组织
Golang语言本身本人没有发现bug, 即便有也早就被大神们捉住了. 唯一的一个感觉貌似bug的, 经常是结构体成员首字母小写, 但是json又无法序列化出来…
慎用cgo. 官方已经声明未来对cgo不提供完整兼容性. 任何一门语言在早期都需要对C做出支持, 但后期完善后的不兼容都是常态。
###golang的time.Format的坑
golang的time.Format设计的和其他语言都不一样, 其他语言总是使用一些格式化字符进行标示, 而golang呢, 查了网上一些坑例子 自己查了下golang的源码, 发现以下代码
// String returns the time formatted using the format string
//  "2006-01-02 15:04:05.999999999 -0700 MST"
func (t Time) String() string {
    return t.Format("2006-01-02 15:04:05.999999999 -0700 MST")
}
尝试将2006-01-02 15:04:05写入到自己的例子中
func nowTime() string {
    return time.Now().Format("2006-01-02 15:04:05")
}
结果返回正确. 询问了下, 据说这个日期是golang诞生的日子… 咋那么自恋呢…

###goruntime

- 尽可能实现无锁机制;
- CGO有限制的使用，它会将该回收的资源推迟到下一次才对其进行回收操作;

![]("image/image1.png")

![]("image/image2.png")

![]("image/image3.png")

![]("image/image4.png")

![]("image/image5.png")

![]("image/image6.png")

![]("image/image7.png")




###go的保留字/关键字(25)
break default func interface select case defer go map struct chan else goto 
package switch const fallthrough if range type continue for import return var <br>
var和const参考2.2Go语言基础里面的变量和常量申明<br>
package和import已经有过短暂的接触<br>
func 用于定义函数和方法<br>
return 用于从函数返回<br>
defer 用于类似析构函数<br>
go 用于并发<br>
select 用于选择不同类型的通讯<br>
interface 用于定义接口<br>
struct 用于定义抽象数据类型<br>
break、case、continue、for、fallthrough、else、if、switch、goto、default流程控制<br>
chan用于channel通讯<br>
type用于声明自定义类型<br>
map用于声明map类型数据<br>
range用于读取slice、map、channel数据<br>

###go数据类型
boolean numeric string derived(指针类型，数组类型，联盟类型，函数类型，切片类型，接口类型，地图类型，管道类型) <br>
####整型：
uint8(0-255)8位无符号整数 uint16(0-65535) uint32(0-4294967295) uint64(0-big) int8(-128 - 127)有符号8位整数 int16(-32768 - 32767) int32 int64
####浮点类型:
float32 float64 complex64 complex128
####其它数值类型:
byte（相当于uint8）
rune (相当于uint32)
uintptr (一个无符号整数来存储指针值的解释的比特位)
<pre>
package main
import "fmt"
func main() {
   var a, b, c = 3, 4, "foo"  
   fmt.Println(a)
   fmt.Println(b)
   fmt.Println(c)
   fmt.Printf("a is of type %T\n", a)
   fmt.Printf("b is of type %T\n", b)
   fmt.Printf("c is of type %T\n", c)
}

Output ==>
3
4
foo
a is of type int
b is of type int
c is of type string
</pre>
%T输出该变量的数据类型<br>
<b>const 关键字</b>
<pre>
  const LENGTH int = 10
  const WIDTH int = 5  
</pre>
这是一个良好的编程习惯大写定义常量。
###Go语言其它运算符
还有其他一些重要的运算符，包括sizeof和?:在Go语言中也支持。
& 返回一个变量的地址 &a; 将得到变量的实际地址  <br>
* 指针的变量  *a; 将指向一个变量
<pre>
package main
import "fmt"
func main() {
   var a int = 4
   var b int32
   var c float32
   var ptr *int
   /* example of type operator */
   fmt.Printf("Line 1 - Type of variable a = %T\n", a );
   fmt.Printf("Line 2 - Type of variable b = %T\n", b );
   fmt.Printf("Line 3 - Type of variable c= %T\n", c );
   /* example of & and * operators */
   ptr = &a	/* 'ptr' now contains the address of 'a'*/
   fmt.Printf("value of a is  %d\n", a);
   fmt.Printf("*ptr is %d.\n", *ptr);
}

Ouptut ==>
Line 1 - Type of variable a = int
Line 2 - Type of variable b = int32
Line 3 - Type of variable c= float32
value of a is  4
*ptr is 4.
</pre>
###表达式Switch
<pre>
package main
import "fmt"
func main() {
   /* local variable definition */
   var grade string = "B"
   var marks int = 90
   switch marks {
      case 90: grade = "A"
      case 80: grade = "B"
      case 50,60,70 : grade = "C"
      default: grade = "D"  
   }
   switch {
      case grade == "A" :
         fmt.Printf("Excellent!\n" )     
      case grade == "B", grade == "C" :
         fmt.Printf("Well done\n" )      
      case grade == "D" :
         fmt.Printf("You passed\n" )      
      case grade == "F":
         fmt.Printf("Better try again\n" )
      default:
         fmt.Printf("Invalid grade\n" );
   }
   fmt.Printf("Your grade is  %s\n", grade );      
}

Output ==>
Well done
Excellent!
Your grade is  A
</pre>


###表达式select
以下规则适用于select语句：

- 可以有任意数量的范围内选择一个case语句。每一种情况下后跟的值进行比较，以及一个冒号。
- 对于case的类型必须是一个通信通道操作。
- 当通道运行下面发生的语句这种情况将执行。在case语句中break不是必需的。
- select语句可以有一个可选默认case，它必须出现在select的结束前。缺省情况下，可用于执行任务时没有的情况下是真实的。在默认情况下break不是必需的。
<pre>
package main
import "fmt"
func main() {
   var c1, c2, c3 chan int
   var i1, i2 int
   select {
      case i1 = <-c1:
         fmt.Printf("received ", i1, " from c1\n")
      case c2 <- i2:
         fmt.Printf("sent ", i2, " to c2\n")
      case i3, ok := (<-c3):  // same as: i3, ok := <-c3
         if ok {
            fmt.Printf("received ", i3, " from c3\n")
         } else {
            fmt.Printf("c3 is closed\n")
         }
      default:
         fmt.Printf("no communication\n")
   }    
}   

Output==>
no communication
</pre>
###go无限循环
<pre>
package main
import "fmt"
func main() {
   for true  {
       fmt.Printf("This loop will run forever.\n");
   }
}

</pre>
tip: 按Ctrl+ C键终止无限循环.
###Go语言continue语句
在Go编程语言中的continue语句有点像break语句。不是强制终止，只是继续循环下一个迭代发生，在两者之间跳过任何代码。
<pre>
package main
import "fmt"
func main() {
   /* local variable definition */
   var a int = 10
   /* do loop execution */
   for a < 20 {
      if a == 15 {
         /* skip the iteration */
         a = a + 1;
         continue;
      }
      fmt.Printf("value of a: %d\n", a);
      a++;     
   }  
}

output ==>
value of a: 10
value of a: 11
value of a: 12
value of a: 13
value of a: 14
value of a: 16
value of a: 17
value of a: 18
value of a: 19
</pre>
###Go语言goto语句
在Go编程语言中的goto语句提供无条件跳转从跳转到标记声明的功能。
注意：使用goto语句是高度劝阻的在任何编程语言，因为它使得难以跟踪程序的控制流程，使程序难以理解，难以修改。使用一个goto任何程序可以改写，以便它不需要goto。
<pre>
package main
import "fmt"
func main() {
   /* local variable definition */
   var a int = 10

   /* do loop execution */
   LOOP: for a < 20 {
      if a == 15 {
         /* skip the iteration */
         a = a + 1
         goto LOOP
      }
      fmt.Printf("value of a: %d\n", a)
      a++     
   }  
}

Output ==>
value of a: 10
value of a: 11
value of a: 12
value of a: 13
value of a: 14
value of a: 16
value of a: 17
value of a: 18
value of a: 19
</pre>

另一个例子：
<pre>
func myFunc() {
    i := 0
Here:   //这行的第一个词，以冒号结束作为标签
    println(i)
    i++
    goto Here   //跳转到Here去
}
</pre>
注意：标签名是大小写敏感的。

###嵌套for
下面的程序使用嵌套for循环从2至100找出的素数.
<pre>
package main
import "fmt"
func main() {
   /* local variable definition */
   var i, j int

   for i=2; i < 100; i++ {
      for j=2; j <= (i/j); j++ {
         if(i%j==0) {
            break; // if factor found, not prime
         }
      }
      if(j > (i/j)) {
         fmt.Printf("%d is prime\n", i);
      }
   }  
}

output ==>
2 is prime
3 is prime
5 is prime
7 is prime
11 is prime
13 is prime
17 is prime
19 is prime
23 is prime
29 is prime
31 is prime
37 is prime
41 is prime
43 is prime
47 is prime
53 is prime
59 is prime
61 is prime
67 is prime
71 is prime
73 is prime
79 is prime
83 is prime
89 is prime
97 is prime
</pre>
###从函数返回多个值
<pre>
package main
import "fmt"
func swap(x, y string) (string, string) {
   return y, x
}
func main() {
   a, b := swap("Mahesh", "Kumar")
   fmt.Println(a, b)
}
Output ==>
Kumar Mahesh
</pre>
###Go语言按值调用
<pre>
package main
import "fmt"
func main() {
   /* local variable definition */
   var a int = 100
   var b int = 200

   fmt.Printf("Before swap, value of a : %d\n", a )
   fmt.Printf("Before swap, value of b : %d\n", b )

   /* calling a function to swap the values */
   swap(a, b)

   fmt.Printf("After swap, value of a : %d\n", a )
   fmt.Printf("After swap, value of b : %d\n", b )
}
func swap(x, y int) int {
   var temp int

   temp = x /* save the value of x */
   x = y    /* put y into x */
   y = temp /* put temp into y */
   return temp;
}

Output ==>
Before swap, value of a :100
Before swap, value of b :200
After swap, value of a :100
After swap, value of b :200
</pre>
这表明，参数值没有被改变，虽然它们已经在函数内部改变。
###Go语言参考调用
通过传递函数参数拷贝参数的地址到形式参数的参考方法调用。在函数内部，地址是访问调用中使用的实际参数。这意味着，对参数的更改会影响传递的参数。
要通过引用传递的值，参数的指针被传递给函数就像任何其他的值。所以，相应的，需要声明函数的参数为指针类型如下面的函数swap()，它的交换两个整型变量的值指向它的参数。
<pre>
package main
import "fmt"
func main() {
   /* local variable definition */
   var a int = 100
   var b int= 200

   fmt.Printf("Before swap, value of a : %d\n", a )
   fmt.Printf("Before swap, value of b : %d\n", b )

   /* calling a function to swap the values.
   * &a indicates pointer to a ie. address of variable a and 
   * &b indicates pointer to b ie. address of variable b.
   */
   swap(&a, &b)

   fmt.Printf("After swap, value of a : %d\n", a )
   fmt.Printf("After swap, value of b : %d\n", b )
}

func swap(x *int, y *int) {
   var temp int
   temp = *x    /* save the value at address x */
   *x = *y    /* put y into x */
   *y = temp    /* put temp into y */
}

output ==>
Before swap, value of a :100
Before swap, value of b :200
After swap, value of a :200
After swap, value of b :100
</pre>

###Go语言函数作为值
Go编程语言提供灵活性，以动态创建函数，并使用它们的值。在下面的例子中，我们已经与初始化函数定义的变量。此函数变量的目仅仅是为使用内置的Math.sqrt()函数。下面是一个例子：
<pre>
package main
import (
   "fmt"
   "math"
)
func main(){
   /* declare a function variable */
   getSquareRoot := func(x float64) float64 {
      return math.Sqrt(x)
   }
   /* use the function */
   fmt.Println(getSquareRoot(9))
}
output ==>
3
</pre>
###Go语言函数闭合
Go编程语言支持匿名函数其可以作为函数闭包。当我们要定义一个函数内联不传递任何名称，它可以使用匿名函数。在我们的例子中，我们创建了一个函数getSequence()将返回另一个函数。该函数的目的是关闭了上层函数的变量i 形成一个闭合。下面是一个例子：
<pre>
package main
import "fmt"
func getSequence() func() int {
   i:=0
   return func() int {
      i+=1
	  return i  
   }
}
func main(){
   /* nextNumber is now a function with i as 0 */
   nextNumber := getSequence()  
   /* invoke nextNumber to increase i by 1 and return the same */
   fmt.Println(nextNumber())
   fmt.Println(nextNumber())
   fmt.Println(nextNumber())
   /* create a new sequence and see the result, i is 0 again*/
   nextNumber1 := getSequence()  
   fmt.Println(nextNumber1())
   fmt.Println(nextNumber1())
}

output ==>
1
2
3
1
2
</pre>
###Go语言方法
Go编程语言支持特殊类型的函数调用的方法。在方法声明的语法中，“接收器”的存在是为了表示容器中的函数。该接收器可用于通过调用函数“.”运算符。下面是一个例子：
<pre>
package main
import (
   "fmt"
   "math"
)
/* define a circle */
type Circle strut {
   x,y,radius float64
}
/* define a method for circle */
func(circle Circle) area() float64 {
   return math.Pi * circle.radius * circle.radius
}
func main(){
   circle := Circle(x:0, y:0, radius:5)
   fmt.Printf("Circle area: %f", circle.area())
}

output ==>
Circle area: 78.539816
</pre>

###Go语言范围规则
在任何编程程序的作用域，其中一个定义的变量可以有它的存在，超出该变量的区域就不能访问。有三个地方变量可以在Go编程语言声明如下：

- 内部函数或这就是所谓的局部变量块
- 所有函数的外面的变量称为全局变量
- 在这被称为形式参数函数的参数的定义
- 让我们来解释一下什么是局部和全局变量和形式参数。

####局部变量
<pre>
package main
import "fmt"
func main() {
   /* local variable declaration */
   var a, b, c int 
   /* actual initialization */
   a = 10
   b = 20
   c = a + b
   fmt.Printf ("value of a = %d, b = %d and c = %d\n", a, b, c)
}
</pre>

####全局变量
全局变量函数的定义之外，通常在程序的顶部。全局变量的值在整个项目的生命周期，它们可以在里面任意的程序中定义的函数中访问。
全局变量可以被任何函数访问。也就是说，全局变量可以在整个程序中使用在它声明之后。下面是使用全局和局部变量的例子：
<pre>
package main
import "fmt"
/* global variable declaration */
var g int
func main() {
   /* local variable declaration */
   var a, b int
   /* actual initialization */
   a = 10
   b = 20
   g = a + b
   fmt.Printf("value of a = %d, b = %d and g = %d\n", a, b, g)
}
</pre>

####形式参数
<pre>
package main
import "fmt"
/* global variable declaration */
var a int = 20;
func main() {
   /* local variable declaration in main function */
   var a int = 10
   var b int = 20
   var c int = 0
   fmt.Printf("value of a in main() = %d\n",  a);
   c = sum( a, b);
   fmt.Printf("value of c in main() = %d\n",  c);
}
/* function to add two integers */
func sum(a, b int) int {
   fmt.Printf("value of a in sum() = %d\n",  a);
   fmt.Printf("value of b in sum() = %d\n",  b);
   return a + b;
}
output ==>
value of a in main() = 10
value of a in sum() = 10
value of b in sum() = 20
value of c in main() = 30
</pre>

####初始化局部和全局变量
当局部变量作为全局变量被初始化其对应值为0。指针被初始化为nil。
###Go语言数组
声明数组
<pre>
var balance [10] float32
</pre>
初始化数组
<pre>
var balance = [5]float32{1000.0, 2.0, 3.4, 7.0, 50.0}
</pre>
访问数组元素：
<pre>
package main
import "fmt"
func main() {
   var n [10]int /* n is an array of 10 integers */
   var i,j int
   /* initialize elements of array n to 0 */         
   for i = 0; i < 10; i++ {
      n[i] = i + 100 /* set element at location i to i + 100 */
   }
   /* output each array element's value */
   for j = 0; j < 10; j++ {
      fmt.Printf("Element[%d] = %d\n", j, n[j] )
   }
}
output ==>
Element[0] = 100
Element[1] = 101
Element[2] = 102
Element[3] = 103
Element[4] = 104
Element[5] = 105
Element[6] = 106
Element[7] = 107
Element[8] = 108
Element[9] = 109
</pre>

####访问二维数组元素
<pre>
package main
import "fmt"
func main() {
   /* an array with 5 rows and 2 columns*/
   var a = [5][2]int{ {0,0}, {1,2}, {2,4}, {3,6},{4,8}}
   var i, j int
   /* output each array element's value */
   for  i = 0; i < 5; i++ {
      for j = 0; j < 2; j++ {
         fmt.Printf("a[%d][%d] = %d\n", i,j, a[i][j] )
      }
   }
}
output ==>
a[0][0]: 0
a[0][1]: 0
a[1][0]: 1
a[1][1]: 2
a[2][0]: 2
a[2][1]: 4
a[3][0]: 3
a[3][1]: 6
a[4][0]: 4
a[4][1]: 8
</pre>

###Go语言传递数组到函数
如果想通过一个一维数组作为函数的参数，就必须声明函数形式参数在以下两种方式之一，以下两种声明方法产生类似的结果，因为每个告诉编译器，一个整数数组将会被接收。类似的方式，可以通过多维数组形式参数。
<pre>
package main
import "fmt"
func main() {
   /* an int array with 5 elements */
   var  balance = []int {1000, 2, 3, 17, 50}
   var avg float32
   /* pass array as an argument */
   avg = getAverage( balance, 5 ) ;
   /* output the returned value */
   fmt.Printf( "Average value is: %f ", avg );
}
func getAverage(arr []int, size int) float32 {
   var i,sum int
   var avg float32  
   for i = 0; i < size;i++ {
      sum += arr[i]
   }
   avg = float32(sum / size)
   return avg;
}
output ==>
Average value is: 214.400000
</pre>
###Go语言结构

####定义结构struct
定义一个结构，必须使用type和struct语句。该结构语句定义了一个新的数据类型，项目不止一个成员。类型语句是结构在我们的案例类型绑定的名称。

####访问结构成员
要访问结构的成员，我们使用成员访问运算符(.)。成员访问运算符是编码作为结构变量名，并且我们希望访问结构部件之间的周期。可使用struct关键字来定义结构类型的变量。
<pre>
package main
import "fmt"
type Books struct {
   title string
   author string
   subject string
   book_id int
}
func main() {
   var Book1 Books        /* Declare Book1 of type Book */
   var Book2 Books        /* Declare Book2 of type Book */
   /* book 1 specification */
   Book1.title = "Go Programming"
   Book1.author = "Mahesh Kumar"
   Book1.subject = "Go Programming Tutorial"
   Book1.book_id = 6495407
   /* book 2 specification */
   Book2.title = "Telecom Billing"
   Book2.author = "Zara Ali"
   Book2.subject = "Telecom Billing Tutorial"
   Book2.book_id = 6495700
   /* print Book1 info */
   fmt.printf( "Book 1 title : %s\n", Book1.title)
   fmt.printf( "Book 1 author : %s\n", Book1.author)
   fmt.printf( "Book 1 subject : %s\n", Book1.subject)
   fmt.printf( "Book 1 book_id : %d\n", Book1.book_id)
   /* print Book2 info */
   fmt.printf( "Book 2 title : %s\n", Book2.title)
   fmt.printf( "Book 2 author : %s\n", Book2.author)
   fmt.printf( "Book 2 subject : %s\n", Book2.subject)
   fmt.printf( "Book 2 book_id : %d\n", Book2.book_id)
}

output ==>
Book 1 title : Go Programming
Book 1 author : Mahesh Kumar
Book 1 subject : Go Programming Tutorial
Book 1 book_id : 6495407
Book 2 title : Telecom Billing
Book 2 author : Zara Ali
Book 2 subject : Telecom Billing Tutorial
Book 2 book_id : 6495700
</pre>

####结构作为函数参数
<pre>
package main
import "fmt"
type Books struct {
   title string
   author string
   subject string
   book_id int
}
func main() {
   var Book1 Books        /* Declare Book1 of type Book */
   var Book2 Books        /* Declare Book2 of type Book */
   /* book 1 specification */
   Book1.title = "Go Programming"
   Book1.author = "Mahesh Kumar"
   Book1.subject = "Go Programming Tutorial"
   Book1.book_id = 6495407
   /* book 2 specification */
   Book2.title = "Telecom Billing"
   Book2.author = "Zara Ali"
   Book2.subject = "Telecom Billing Tutorial"
   Book2.book_id = 6495700
   /* print Book1 info */
   printBook(Book1)
   /* print Book2 info */
   printBook(Book2)
}
func printBook( book Books )
{
   fmt.printf( "Book title : %s\n", book.title);
   fmt.printf( "Book author : %s\n", book.author);
   fmt.printf( "Book subject : %s\n", book.subject);
   fmt.printf( "Book book_id : %d\n", book.book_id);
}
output ==>
Book title : Go Programming
Book author : Mahesh Kumar
Book subject : Go Programming Tutorial
Book book_id : 6495407
Book title : Telecom Billing
Book author : Zara Ali
Book subject : Telecom Billing Tutorial
Book book_id : 6495700
</pre>

####指针结构
可以非常相似定义指针结构的方式，为您定义指向任何其他变量:
<pre>
var struct_pointer *Books
</pre>
使用结构指针重新写上面例子：
<pre>
package main

import "fmt"

type Books struct {
   title string
   author string
   subject string
   book_id int
}

func main() {
   var Book1 Books        /* Declare Book1 of type Book */
   var Book2 Books        /* Declare Book2 of type Book */
 
   /* book 1 specification */
   Book1.title = "Go Programming"
   Book1.author = "Mahesh Kumar"
   Book1.subject = "Go Programming Tutorial"
   Book1.book_id = 6495407

   /* book 2 specification */
   Book2.title = "Telecom Billing"
   Book2.author = "Zara Ali"
   Book2.subject = "Telecom Billing Tutorial"
   Book2.book_id = 6495700
 
   /* print Book1 info */
   printBook(&Book1)

   /* print Book2 info */
   printBook(&Book2)
}
func printBook( book *Books )
{
   fmt.printf( "Book title : %s\n", book.title);
   fmt.printf( "Book author : %s\n", book.author);
   fmt.printf( "Book subject : %s\n", book.subject);
   fmt.printf( "Book book_id : %d\n", book.book_id);
}
output ==>
Book title : Go Programming
Book author : Mahesh Kumar
Book subject : Go Programming Tutorial
Book book_id : 6495407
Book title : Telecom Billing
Book author : Zara Ali
Book subject : Telecom Billing Tutorial
Book book_id : 6495700
</pre>


###Go语言映射
Go编程提供另一个重要的数据类型是映射，唯一映射一个键到一个值。一个键要使用在以后检索值的对象。给定的键和值，可以在一个Map对象存储的值。值存储后，您可以使用它的键检索。

####定义映射
必须使用make函数来创建一个映射。
<pre>
/* declare a variable, by default map will be nil*/
var map_variable map[key_data_type]value_data_type

/* define the map as nil map can not be assigned any value*/
map_variable = make(map[key_data_type]value_data_type)
</pre>
例子:
<pre>
package main
import "fmt"
func main {
   var coutryCapitalMap map[string]string
   /* create a map*/
   coutryCapitalMap = make(map[string]string)
   
   /* insert key-value pairs in the map*/
   countryCapitalMap["France"] = "Paris"
   countryCapitalMap["Italy"] = "Rome"
   countryCapitalMap["Japan"] = "Tokyo"
   countryCapitalMap["India"] = "New Delhi"
   
   /* print map using keys*/
   for country := range countryCapitalMap {
      fmt.Println("Capital of",country,"is",countryCapitalMap[country])
   }
   
   /* test if entry is present in the map or not*/
   captial, ok := countryCapitalMap["United States"]
   /* if ok is true, entry is present otherwise entry is absent*/
   if(ok){
      fmt.Println("Capital of United States is", capital)  
   }else {
      fmt.Println("Capital of United States is not present") 
   }
}

output ==>
Capital of India is New Delhi
Capital of France is Paris
Capital of Italy is Rome
Capital of Japan is Tokyo
Capital of United States is not present
</pre>

####delete() 函数
delete()函数是用于从映射中删除一个项目。映射和相应的键将被删除。下面是一个例子：
<pre>
package main
import "fmt"
func main {   
   /* create a map*/
   coutryCapitalMap := map[string] string {"France":"Paris","Italy":"Rome","Japan":"Tokyo","India":"New Delhi"}
   
   fmt.Println("Original map")   
   
   /* print map */
   for country := range countryCapitalMap {
      fmt.Println("Capital of",country,"is",countryCapitalMap[country])
   }
   
   /* delete an entry */
   delete(countryCapitalMap,"France");
   fmt.Println("Entry for France is deleted")  
   
   fmt.Println("Updated map")   
   
   /* print map */
   for country := range countryCapitalMap {
      fmt.Println("Capital of",country,"is",countryCapitalMap[country])
   }
}

output==>
Original Map
Capital of France is Paris
Capital of Italy is Rome
Capital of Japan is Tokyo
Capital of India is New Delhi
Entry for France is deleted
Updated Map
Capital of India is New Delhi
Capital of Italy is Rome
Capital of Japan is Tokyo
</pre>

####Go语言递归
递归是以相似的方式重复项目的过程。同样适用于编程语言中，如果一个程序可以让你调用同一个函数被调用的函数，递归调用函数内使用如下。
<pre>
func recursion() {
   recursion() /* function calls itself */
}
func main() {
   recursion()
}
</pre>
Go编程语言支持递归，即要调用的函数本身。但是在使用递归时，程序员需要谨慎确定函数的退出条件，否则会造成无限循环。
递归函数是解决许多数学问题想计算一个数阶乘非常有用的，产生斐波系列等。

####数字阶乘
<pre>
package main
import "fmt"
func factorial(i int) {
   if(i <= 1) {
      return 1
   }
   return i * factorial(i - 1)
}
func main {  
    var i int = 15
    fmt.Printf("Factorial of %d is %d\n", i, factorial(i))
}
output ==>
Factorial of 15 is 2004310016
</pre>

####斐波那契系列
<pre>
package main

import "fmt"

func fibonaci(i int) {
   if(i == 0) {
      return 0
   }
   if(i == 1) {
      return 1
   }
   return fibonaci(i-1) + fibonaci(i-2)
}

func main() {
    var i int
    for i = 0; i < 10; i++ {
       fmt.Printf("%d\t%n", fibonaci(i))
    }    
}
outpt ==>
0	1	1	2	3	5	8	13	21	34
</pre>
###Go语言错误处理
使用返回值和错误消息。
<pre>
if err != nil {
   fmt.Println(err)
}
</pre>
例子：
<pre>
package main

import "errors"
import "fmt"
import "math"

func Sqrt(value float64)(float64, error) {
   if(value < 0){
      return 0, errors.New("Math: negative number passed to Sqrt")
   }
   return math.Sqrt(value)
}

func main() {
   result, err:= Sqrt(-1)

   if err != nil {
      fmt.Println(err)
   }else {
      fmt.Println(result)
   }
   
   result, err = Sqrt(9)

   if err != nil {
      fmt.Println(err)
   }else {
      fmt.Println(result)
   }
}
output ==>
Math: negative number passed to Sqrt
3
</pre>

###defer
Go语言中有种不错的设计，即延迟（defer）语句，你可以在函数中添加多个defer语句。当函数执行到最后时，这些defer语句会按照<b>逆序</b>执行，最后该函数返回。特别是当你在进行一些打开资源的操作时，遇到错误需要提前返回，在返回前你需要关闭相应的资源，不然很容易造成资源泄露等问题。如下代码所示，我们一般写打开一个资源是这样操作的：
<pre>
func ReadWrite() bool {
    file.Open("file")
// 做一些工作
    if failureX {
        file.Close()
        return false
    }

    if failureY {
        file.Close()
        return false
    }

    file.Close()
    return true
}
</pre>
我们看到上面有很多重复的代码，Go的defer有效解决了这个问题。使用它后，不但代码量减少了很多，而且程序变得更优雅。在defer后指定的函数会在函数退出前调用。
<pre>
func ReadWrite() bool {
    file.Open("file")
    defer file.Close()
    if failureX {
        return false
    }
    if failureY {
        return false
    }
    return true
}
</pre>
如果有很多调用defer，那么defer是采用后进先出模式，所以如下代码会输出4 3 2 1 0
<pre>
for i := 0; i < 5; i++ {
    defer fmt.Printf("%d ", i)
}
</pre>

###面向对象
前面两章我们介绍了函数和struct，那你是否想过函数当作struct的字段一样来处理呢？今天我们就讲解一下函数的另一种形态，带有接收者的函数，我们称为<b>method</b>
现在假设有这么一个场景，你定义了一个struct叫做长方形，你现在想要计算他的面积，那么按照我们一般的思路应该会用下面的方式来实现:
<pre>
package main
import "fmt"
type Rectangle struct {
    width, height float64
}
func area(r Rectangle) float64 {
    return r.width*r.height
}
func main() {
    r1 := Rectangle{12, 2}
    r2 := Rectangle{9, 4}
    fmt.Println("Area of r1 is: ", area(r1))
    fmt.Println("Area of r2 is: ", area(r2))
}
</pre>
下面我们用最开始的例子用method来实现：
<pre>
package main
import (
    "fmt"
    "math"
)
type Rectangle struct {
    width, height float64
}
type Circle struct {
    radius float64
}

func (r Rectangle) area() float64 {
    return r.width*r.height
}

func (c Circle) area() float64 {
    return c.radius * c.radius * math.Pi
}


func main() {
    r1 := Rectangle{12, 2}
    r2 := Rectangle{9, 4}
    c1 := Circle{10}
    c2 := Circle{25}

    fmt.Println("Area of r1 is: ", r1.area())
    fmt.Println("Area of r2 is: ", r2.area())
    fmt.Println("Area of c1 is: ", c1.area())
    fmt.Println("Area of c2 is: ", c2.area())
}
</pre>

####method继承
前面一章我们学习了字段的继承，那么你也会发现Go的一个神奇之处，method也是可以继承的。如果匿名字段实现了一个method，那么包含这个匿名字段的struct也能调用该method。让我们来看下面这个例子:
<pre>
package main
import "fmt"

type Human struct {
    name string
    age int
    phone string
}

type Student struct {
    Human //匿名字段
    school string
}

type Employee struct {
    Human //匿名字段
    company string
}

//在human上面定义了一个method
func (h *Human) SayHi() {
    fmt.Printf("Hi, I am %s you can call me on %s\n", h.name, h.phone)
}

func main() {
    mark := Student{Human{"Mark", 25, "222-222-YYYY"}, "MIT"}
    sam := Employee{Human{"Sam", 45, "111-888-XXXX"}, "Golang Inc"}

    mark.SayHi()
    sam.SayHi()
}
</pre>

####method重写
上面的例子中，如果Employee想要实现自己的SayHi,怎么办？简单，和匿名字段冲突一样的道理，我们可以在Employee上面定义一个method，重写了匿名字段的方法。请看下面的例子:
<pre>
package main
import "fmt"

type Human struct {
    name string
    age int
    phone string
}

type Student struct {
    Human //匿名字段
    school string
}

type Employee struct {
    Human //匿名字段
    company string
}

//Human定义method
func (h *Human) SayHi() {
    fmt.Printf("Hi, I am %s you can call me on %s\n", h.name, h.phone)
}

//Employee的method重写Human的method
func (e *Employee) SayHi() {
    fmt.Printf("Hi, I am %s, I work at %s. Call me on %s\n", e.name,
        e.company, e.phone) //Yes you can split into 2 lines here.
}

func main() {
    mark := Student{Human{"Mark", 25, "222-222-YYYY"}, "MIT"}
    sam := Employee{Human{"Sam", 45, "111-888-XXXX"}, "Golang Inc"}

    mark.SayHi()
    sam.SayHi()
}
</pre>

###并发
有人把Go比作21世纪的C语言，第一是因为Go语言设计简单，第二，21世纪最重要的就是并行程序设计，而Go从语言层面就支持了并行。

####1.goroutine
goroutine是Go并行设计的核心。goroutine说到底其实就是线程，但是它比线程更小，十几个goroutine可能体现在底层就是五六个线程，Go语言内部帮你实现了这些goroutine之间的内存共享。执行goroutine只需极少的栈内存(大概是4~5KB)，当然会根据相应的数据伸缩。也正因为如此，可同时运行成千上万个并发任务。goroutine比thread更易用、更高效、更轻便。
goroutine是通过Go的runtime管理的一个线程管理器。goroutine通过go关键字实现了，其实就是一个普通的函数。<br>
go hello(a, b, c)<br>
通过关键字go就启动了一个goroutine。我们来看一个例子
<pre>
package main

import (
    "fmt"
    "runtime"
)

func say(s string) {
    for i := 0; i < 5; i++ {
        runtime.Gosched()
        fmt.Println(s)
    }
}

func main() {
    go say("world") //开一个新的Goroutines执行
    say("hello") //当前Goroutines执行
}

// 以上程序执行后将输出：
// hello
// world
// hello
// world
// hello
// world
// hello
// world
// hello
</pre>
我们可以看到go关键字很方便的就实现了并发编程。 上面的多个goroutine运行在同一个进程里面，共享内存数据，不过设计上我们要遵循：不要通过共享来通信，而要通过通信来共享。

####2.channels(channel)
goroutine运行在相同的地址空间，因此访问共享内存必须做好同步。那么goroutine之间如何进行数据的通信呢，Go提供了一个很好的通信机制channel。channel可以与Unix shell 中的双向管道做类比：可以通过它发送或者接收值。这些值只能是特定的类型：channel类型。定义一个channel时，也需要定义发送到channel的值的类型。注意，必须使用make 创建channel：
<pre>
ci := make(chan int)
cs := make(chan string)
cf := make(chan interface{})
</pre>
channel通过操作符<-来接收和发送数据
<pre>
ch <- v    // 发送v到channel ch.
v := <-ch  // 从ch中接收数据，并赋值给v
</pre>
我们把这些应用到我们的例子中来：
<pre>
package main

import "fmt"

func sum(a []int, c chan int) {
    total := 0
    for _, v := range a {
        total += v
    }
    c <- total  // send total to c
}

func main() {
    a := []int{7, 2, 8, -9, 4, 0}

    c := make(chan int)
    go sum(a[:len(a)/2], c)
    go sum(a[len(a)/2:], c)
    x, y := <-c, <-c  // receive from c

    fmt.Println(x, y, x + y)
}
</pre>
默认情况下，channel接收和发送数据都是阻塞的，除非另一端已经准备好，这样就使得Goroutines同步变的更加的简单，而不需要显式的lock。所谓阻塞，也就是如果读取（value := <-ch）它将会被阻塞，直到有数据接收。其次，任何发送（ch<-5）将会被阻塞，直到数据被读出。无缓冲channel是在多个goroutine之间同步很棒的工具。

####3.Buffered Channels
上面我们介绍了默认的非缓存类型的channel，不过Go也允许指定channel的缓冲大小，很简单，就是channel可以存储多少元素。ch:= make(chan bool, 4)，创建了可以存储4个元素的bool 型channel。在这个channel 中，前4个元素可以无阻塞的写入。当写入第5个元素时，代码将会阻塞，直到其他goroutine从channel 中读取一些元素，腾出空间。
<pre>
ch := make(chan type, value)
value == 0 ! 无缓冲（阻塞）
value > 0 ! 缓冲（非阻塞，直到value 个元素）
</pre>
我们看一下下面这个例子，你可以在自己本机测试一下，修改相应的value值
<pre>
package main

import "fmt"

func main() {
    c := make(chan int, 2)//修改2为1就报错，修改2为3可以正常运行
    c <- 1
    c <- 2
    fmt.Println(<-c)
    fmt.Println(<-c)
}
    //修改为1报如下的错误:
    //fatal error: all goroutines are asleep - deadlock!
</pre>

####4.Range和Close
上面这个例子中，我们需要读取两次c，这样不是很方便，Go考虑到了这一点，所以也可以通过range，像操作slice或者map一样操作缓存类型的channel，请看下面的例子:
<pre>
package main

import (
    "fmt"
)

func fibonacci(n int, c chan int) {
    x, y := 1, 1
    for i := 0; i < n; i++ {
        c <- x
        x, y = y, x + y
    }
    close(c)
}

func main() {
    c := make(chan int, 10)
    go fibonacci(cap(c), c)
    for i := range c {
        fmt.Println(i)
    }
}
</pre>
for i := range c能够不断的读取channel里面的数据，直到该channel被显式的关闭。上面代码我们看到可以显式的关闭channel，生产者通过内置函数close关闭channel。关闭channel之后就无法再发送任何数据了，在消费方可以通过语法v, ok := <-ch测试channel是否被关闭。如果ok返回false，那么说明channel已经没有任何数据并且已经被关闭。
记住应该在生产者的地方关闭channel，而不是消费的地方去关闭它，这样容易引起panic
另外记住一点的就是channel不像文件之类的，不需要经常去关闭，只有当你确实没有任何发送数据了，或者你想显式的结束range循环之类的

####5.Select
我们上面介绍的都是只有一个channel的情况，那么如果存在多个channel的时候，我们该如何操作呢，Go里面提供了一个关键字select，通过select可以监听channel上的数据流动。

select默认是阻塞的，只有当监听的channel中有发送或接收可以进行时才会运行，当多个channel都准备好的时候，select是随机的选择一个执行的。
<pre>
package main

import "fmt"

func fibonacci(c, quit chan int) {
    x, y := 1, 1
    for {
        select {
        case c <- x:
            x, y = y, x + y
        case <-quit:
            fmt.Println("quit")
            return
        }
    }
}

func main() {
    c := make(chan int)
    quit := make(chan int)
    go func() {
        for i := 0; i < 10; i++ {
            fmt.Println(<-c)
        }
        quit <- 0
    }()
    fibonacci(c, quit)
}
</pre>
在select里面还有default语法，select其实就是类似switch的功能，default就是当监听的channel都没有准备好的时候，默认执行的（select不再阻塞等待channel）。
<pre>
select {
case i := <-c:
    // use i
default:
    // 当c阻塞的时候执行这里
}
</pre>

####6.超时
有时候会出现goroutine阻塞的情况，那么我们如何避免整个程序进入阻塞的情况呢？我们可以利用select来设置超时，通过如下的方式实现：
<pre>
func main() {
    c := make(chan int)
    o := make(chan bool)
    go func() {
        for {
            select {
                case v := <- c:
                    println(v)
                case <- time.After(5 * time.Second):
                    println("timeout")
                    o <- true
                    break
            }
        }
    }()
    <- o
}
</pre>

####7.runtime goroutine
runtime包中有几个处理goroutine的函数：

- Goexit
退出当前执行的goroutine，但是defer函数还会继续调用

- Gosched
让出当前goroutine的执行权限，调度器安排其他等待的任务运行，并在下次某个时候从该位置恢复执行。

- NumCPU
返回 CPU 核数量

- NumGoroutine
返回正在执行和排队的任务总数

- GOMAXPROCS
用来设置可以并行计算的CPU核数的最大值，并返回之前的值。

###指针
声明指针：
var ip *int // pointer to an integer
var fp *float32 //pointer to a float
指针的作用很多，其实说白了就是直接操作内存，好处是：

- 效率更高，这个很容易理解，直接操作内存，效率必然更高
- 可以写复杂度更高的数据
- 结构，这个也好理解，程序员可以操作内存，当然可以写出灵活、复杂的数据结构
- 编写出简洁、紧凑、高效的程序
<pre>
package main
import (
	"fmt"
)
func main () {
	type person struct {
	Age int
	phone int
	name string
	}
	var s=person{2333,1222222,""}
	var p *person
	p =&s
	fmt.Printf("%p, %v\n",p,p.phone)
}
output ==>
0xc082004640,1222222
</pre>

