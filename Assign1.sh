echo -e "           \nADDRESS BOOK\n"
ch=0
fname=""

create() {
    echo -e "\n"
    read -p "Enter Filename: " fname
    touch "$fname"
    echo -e "\nid\tname\tmobile_no\tlocation\n" > "$fname"
    echo "Address book created successfully."
}

view() {
    if [[ -f $fname ]]; then
        cat "$fname"
    else
        echo "No file found. Please create an address book first."
    fi
}

insert() {
    if [[ -f $fname ]]; then
        echo -e "\n"
        read -p "Enter id: " id
        read -p "Enter name: " name
        read -p "Enter mobile number: " mno
        read -p "Enter location: " loc
        echo -e "$id\t$name\t$mno\t$loc" >> "$fname"
        echo "Record inserted successfully."
    else
        echo "No file found. Please create an address book first."
    fi
}

delete() {
    if [[ -f $fname ]]; then
        echo -e "\n"
        read -p "Enter Student ID to delete: " id
        if grep -w "$id" "$fname"; then
            grep -wv "$id" "$fname" > temp && mv temp "$fname"
            echo "Record deleted successfully."
        else
            echo "Record not found."
        fi
    else
        echo "No file found. Please create an address book first."
    fi
}

modify() {
    if [[ -f $fname ]]; then
        echo -e "\n"
        read -p "Enter Student ID to modify: " id
        if grep -w "$id" "$fname"; then
            echo -e "\n"
            read -p "Enter new id: " new_id
            read -p "Enter new name: " new_name
            read -p "Enter new mobile number: " new_mno
            read -p "Enter new location: " new_loc
            sed "/^$id/c$new_id\t$new_name\t$new_mno\t$new_loc" "$fname" > temp && mv temp "$fname"
            echo "Record modified successfully."
        else
            echo "Record not found."
        fi
    else
        echo "No file found. Please create an address book first."
    fi
}

search() {
    if [[ -f $fname ]]; then
        echo -e "\n"
        read -p "Enter Student ID to search: " id
        if grep -w "$id" "$fname"; then

            echo -e "\nRecord found."
        else
            echo -e "\nRecord not found."
        fi
    else
        echo "No file found. Please create an address book first."
    fi
}

# Menu
while [ "$ch" -ne 7 ]
do
    echo -e "\n1) Create Address Book"
    echo -e "2) View Address Book"
    echo -e "3) Insert a Record"
    echo -e "4) Delete a Record"
    echo -e "5) Modify a Record"
    echo -e "6) Search a Record"
    echo -e "7) Exit\n"
    read -p "Enter your choice: " ch

    # Ensure ch is a number
    if ! [[ "$ch" =~ ^[0-9]+$ ]]; then
        echo "Invalid input. Please enter a number between 1 and 7."
        ch=0
        continue
    fi

    case $ch in 
        1) create ;;
        2) view ;;
        3) insert ;;
        4) delete ;;
        5) modify ;;
        6) search ;;
        7) echo "Exiting...";;
        *) echo "Invalid choice. Please try again." ;;
    esac
done

