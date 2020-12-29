# flowrian
My own designed language and compiler.   
This compiler(nameed `flower`) works to change `flowrian code` to assembler of [tvm](https://github.com/woogyun/tvm).    
   
[!] this is not a perfect language or perfect compiler.    
(i just made this as a term project of compiler lecture.) 
```
#add::integer, integer -> integer (
  start $a, $b; 
  $c::integer = $a + $b; 
  end $c; 
)

#main :: void -> integer (
  start ;
  $greeting::char[20] = "helloFlowrian"; 
  @ <- $greeting; 
  $sum :: integer; 
  $sum = #add 3, 4; 
  @ <- $sum;  
  end 1; 
)
```
<br>
<br> 

# How To Use? 
### Download and Build 
```shell
#download bison and flex first 
sudo apt-get install flex bison 

git clone https://github.com/zetwhite/flowrian.git
cd flowrian 
make

git clone https://github.com/woogyun/tvm.git 
cd tvm 
cp make.bat make
make 
```
### write your flowrian code 
you can get more example code from [exampleCode](https://github.com/zetwhite/flowrian/tree/main/exampleCode). 
```
--fibo.fw
#getFibo::integer->integer(
  start $number; 

  $result::integer; 
  if($number <= 1){
    $result = $number; 
  }
  else{
    $result = (#getFibo ($number - 1)) + (#getFibo ($number - 2)); 
  }

  end $result; 
)


#main::void->void(
  start; 
  
  $number::integer = 6; 
  @ <- "FiboOf6Is"; 
  @ <- #getFibo $number; 

  end; 
)
```

### compile and run 
```shell
./flower -t -f -o fibo.t < fibo.fw
# this options show symbol table and function list you defined
# you can get fibo.t as output 

# goto tvm and run fibo.t code 
./tvm fibo.t 
```
<br>
<br> 

# How Does It Work? 
This is a simple example of working process. 
start with, #add function. 
```
#add::integer, integer -> integer (
	 	start $a, $b;
		$c::integer;
		$c = $a + $b; 
		end $c;
)
``` 

### parse and get AST 
for specific, you can check `Block` and `Node` class in ast folder. 
there are a number of child classes of `Block` and `Node` class to represent various syntax of flowrian. 

<img src="/img/ast.PNG" width="40%" height="30%" title="AST example"></img>

### create Symbol tables 
there is a Symbol table per function.   
for more info, you can check symtab folder(`Symtab` class, `SymNode` class) and `AddSymbol` function of Block class.    

<img src="/img/symtab01.PNG" width="40%" height="30%" title="AST example"></img>
<img src="/img/symtab02.PNG" width="40%" title="AST example"></img>


### type checking
There are some points to be checked before generating code.    
If there is an assignment statment, you have to check left side and right side are same type(or type casting is possible) and also, whether left side is a variable that value can be changed or not.     
for more info, check `checkType` function of Block class and `calcType` function of Node class. 

<img src="/img/typechecking03.PNG" width="40%" title="AST example"></img>
  

### generate code 
there are some routine for each statement to create a valid tvm assembly code.   
check `codeGen` function of Block class and `calcNode` function of Node class. 
