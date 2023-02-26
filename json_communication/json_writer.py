from_user = "a"
while True:
    file = open("abc.json", "w") 
    file.write(from_user) 
    file.close() 
    from_user = input("Enter a message: ")