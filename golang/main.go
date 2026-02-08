package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

var reader = bufio.NewReader(os.Stdin)

func ps(a ...any) {
	fmt.Println(a...)
}

func read() (string) {
	line, err := reader.ReadString('\n')
	if err != nil{
		return ""
	}
	return strings.TrimSpace(line)
}

func pre() {

}
func part1(){

}
func part2(){

}
func main(){
	isPart1:=true;
	if isPart1{part1();
	}    else {part2();}
}

