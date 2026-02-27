from functools import reduce

numeros = [1,2,3,4]
total = reduce(lambda a,b : a+b , numeros);
print(total)
