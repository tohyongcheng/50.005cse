VALID='secret'
echo 'Please Enter Password: '
read INPUT

if [ "$INPUT" == "$VALID" ]
	then
		echo "You have access"
	else
		echo "Access denied!"
		exit
fi

echo "Welcome"