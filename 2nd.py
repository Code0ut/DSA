'''Implement all functions of a dictionary (ADT) using hashing and handle collision using
chaining with/ without replacement. Data: Set of (key, value) pairs, Keys are mapped to
values, Keys must be comparable, Keys must be unique. standard Operations: Insert(key,
value), Find(key), Delete (key)'''

class ADT:
	def __init__(self,size):
		self.size=size
		self.table=[[] for _ in range(size)]
	
	def hashFunc(self,key):
		return hash(key)%self.size
	
	def insert(self,key,value):
		index=self.hashFunc(key)
		for i in self.table[index]:
			if i[0]==key:
				self.table[index][i] = (key, value)
				return
		self.table[index].append((key,value))

	def search(self,key):
		index=self.hashFunc(key)
		for i in self.table[index]:
			if i[0]==key:
				return index
		return -1
	
	def delete(self, key):
    		index = self.hashFunc(key)
    		for i, (k, v) in enumerate(self.table[index]):
        		if k == key:
            			del self.table[index][i]
            			return
		

	def display(self):
		print("Dictionary\n")
		for i in self.table:
			print(i,"\n")

def main():
	Dict=ADT(10)
	while True:
		ch=int(input("MAIN MENU\n1.Insert\n2.Find\n3.Delete\n4.Display\n5.Exit"))
		if(ch==1):
			key=input("Enter the key: ")
			value=input("Enter the value: ")
			Dict.insert(key,value)
		elif(ch==2):
			key=input("Enter key to be searched: ")
			ind=Dict.search(key)
			if(ind>-1):
				print(key,"found at",ind)
			else:
				print(key,"not found")
		elif(ch==3):
			key=input("Enter key to be deleted: ")
			Dict.delete(key)
		elif(ch==4):
			Dict.display()
		elif(ch==5):
			break
		else:
			print("Invalid Choice")
		print("\n")

if __name__=='__main__':
	main()
