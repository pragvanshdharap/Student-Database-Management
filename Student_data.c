#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct data {
    int roll_no;
    char name[50];
    char gender;
    char phone_number[11];  // 10 digits + null terminator
    struct data* next;
} data;

int check_roll_num(data *head,int roll_no){
    data *temp = head;
    while (temp != NULL) {
        if (temp->roll_no == roll_no) {
            return 1;  // Duplicate found
        }
        temp = temp->next;
    }
    return 0;  // No duplicate
}

int check_phone_num(const char *phone_number){
      if (strlen(phone_number) != 10) {
        return 0;  // Invalid length
    }
    return 1;
}

int check_gender(char  gender){

     if (gender == 'M' || gender == 'F') {
            return 1;
        } else {
            printf("Invalid input! Please enter 'M' or 'F'.\n");
            return 0;
        }
}

void insert(data **head){
    data *temp=*head;
    data *t1=*head;

    temp=(data*)malloc(sizeof(data));

    // Input roll number
    printf("Enter roll number of student: ");
    scanf("%d", &temp->roll_no);

    if (check_roll_num(*head, temp->roll_no)) {
        printf("Error: Roll number %d already exists. Cannot insert duplicate.\n", temp->roll_no);
        return;
    }  
   
    // Input name
    printf("Enter name of student: ");
    getchar();  // Consume any leftover newline from the previous input
    fgets(temp->name, 50, stdin);
    temp->name[strcspn(temp->name, "\n")] = '\0';  // Remove trailing newline
  
    // Input gender
    do {
        printf("Enter gender (M/F): ");
        scanf(" %c", &temp->gender);  // Note the space before %c to consume any leftover newline
    } while (!check_gender(temp->gender));


    // Input phone number
    do {
        printf("Enter phone number (10 digits): ");
        scanf("%s", temp->phone_number);
    } while (!check_phone_num(temp->phone_number));

    
    temp->next = NULL;

    if (*head == NULL) {
        *head = temp;
    } else {
        while (t1->next != NULL) {
            t1 = t1->next;
        }
        t1->next = temp;
    }

    printf("Record with roll number %d inserted successfully.\n", temp->roll_no);
}

void delete(data **head, int roll_num) {
    data *temp = *head, *prev = NULL;

    // Check if the head node itself needs to be deleted
    if (temp != NULL && temp->roll_no == roll_num) {
        *head = temp->next;  // Update head to the next node
        free(temp);  // Free memory of the old head
        printf("Record with roll number %d deleted.\n", roll_num);
        return;
    }

    // Traverse the list to find the node to be deleted
    while (temp != NULL && temp->roll_no != roll_num) {
        prev = temp;
        temp = temp->next;
    }

    // If the node was not found
    if (temp == NULL) {
        printf("Record with roll number %d not found.\n", roll_num);
        return;
    }

    // Unlink the node from the list
    prev->next = temp->next;

    // Free the memory of the node to be deleted
    free(temp);
    printf("Record with roll number %d deleted.\n", roll_num);
}


void sort(data **head){
    if (*head == NULL || (*head)->next == NULL) {
        return;  // No need to sort if the list is empty or has only one element
    }

    data *i, *j; 
    int temp_roll_no;
    char temp_name[50], temp_gender, temp_phone_number[11];

    for (i = *head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->roll_no > j->roll_no) {
                // Swap roll number
                temp_roll_no = i->roll_no;
                i->roll_no = j->roll_no;
                j->roll_no = temp_roll_no;

                // Swap name
                strcpy(temp_name, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, temp_name);

                // Swap gender
                temp_gender = i->gender;
                i->gender = j->gender;
                j->gender = temp_gender;

                // Swap phone number
                strcpy(temp_phone_number, i->phone_number);
                strcpy(i->phone_number, j->phone_number);
                strcpy(j->phone_number, temp_phone_number);
            }
        }
    }
}

void display(data *head){

    data *t1=head;

    sort(&head);
    
    if(head == NULL){
        printf("No data to display.\n");
        return;
    }

    while (t1!=NULL){
        printf("Roll Number-%d\n",t1->roll_no);
        printf("Name of student-%s\n",t1->name);
        printf("Gender of student-%c\n",t1->gender);
        printf("Phone Number of student -%s\n",t1->phone_number);     
        t1=t1->next;
    }
    
}

void modify(data **head){

    int roll_no;
    printf("Enter roll number of student to modify: ");
    scanf("%d", &roll_no);
    
    data* temp = *head;
    while (temp != NULL && temp->roll_no != roll_no) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student with roll number %d not found.\n", roll_no);
        return head;
    }

    printf("*******************MODIFYING STUDENT %d*********************\n", roll_no);
    printf("1. Modify Name\n");
    printf("2. Modify Gender\n");
    printf("3. Modify Phone Number\n");

    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("Enter new name: ");
            fgets(temp->name, sizeof(temp->name), stdin);  // Ensure temp->name has enough space
            temp->name[strcspn(temp->name, "\n")] = '\0';  // Optional: Remove trailing newline from fgets

            break;

        case 2:
            do {
                printf("Enter new gender (M/F): ");
                scanf(" %c", &temp->gender);
            } while (!check_gender(temp->gender));
            break;

        case 3:
            printf("Enter new phone number (10 digits): ");
            do {
                scanf("%s", temp->phone_number);
            } while (!check_phone_num(temp->phone_number));
            break;


                default: printf("Invalid choice\n");

            }

    printf("Student data modified successfully.\n");

}

void search(data *head,int roll_num){
    data *temp = head;

    while (temp != NULL && temp->roll_no != roll_num) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Record with roll number %d not found.\n", roll_num);
        return;
    }

    printf("Record found:\n");
    printf("Roll Number: %d\n", temp->roll_no);
    printf("Name: %s\n", temp->name);
    printf("Gender: %c\n", temp->gender);
    printf("Phone Number: %s\n\n", temp->phone_number);
}

void sort_by_roll_no(data **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;  // No need to sort if the list is empty or has only one element
    }

    data *i, *j;
    int temp_roll_no;
    char temp_name[50], temp_gender, temp_phone_number[11];

    for (i = *head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->roll_no > j->roll_no) {
                // Swap roll number
                temp_roll_no = i->roll_no;
                i->roll_no = j->roll_no;
                j->roll_no = temp_roll_no;

                // Swap name
                strcpy(temp_name, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, temp_name);

                // Swap gender
                temp_gender = i->gender;
                i->gender = j->gender;
                j->gender = temp_gender;

                // Swap phone number
                strcpy(temp_phone_number, i->phone_number);
                strcpy(i->phone_number, j->phone_number);
                strcpy(j->phone_number, temp_phone_number);
            }
        }
    }
}

void save_to_file(data *head) {
    // Sort the list before saving
    sort_by_roll_no(&head);

    FILE *file = fopen("students_data.txt", "w");
    if (!file) {
        printf("Error opening file for saving.\n");
        return;
    }

    data *temp = head;
    while (temp != NULL) {
        // Save data with additional text labels
        fprintf(file, "Roll Number-%d\n", temp->roll_no);
        fprintf(file, "Name of student-%s\n", temp->name);
        fprintf(file, "Gender-%c\n", temp->gender);
        fprintf(file, "Phone number-%s\n\n", temp->phone_number);
        temp = temp->next;
    }

    fclose(file);
    printf("Sorted data saved to file successfully.\n");
}

// Load the list from a file
void load_from_file(data **head) {
    FILE *file = fopen("students_data.txt", "r");
    if (!file) {
        printf("Error opening file for loading.\n");
        return;
    }

    int roll_no;
    char name[50], gender, phone_number[11];
    char buffer[100]; // Buffer to read lines from the file

    while (fgets(buffer, sizeof(buffer), file)) {
        // Read and extract roll number
        if (sscanf(buffer, "Roll Number-%d", &roll_no) != 1) continue;

        // Read and extract name
        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "Name of student-%s", name);

        // Read and extract gender
        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "Gender-%c", &gender);

        // Read and extract phone number
        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "Phone number-%s", phone_number);

        // Allocate memory for the new student data
        data *temp = (data*)malloc(sizeof(data));
        if (temp == NULL) {
            printf("Error: Memory allocation failed\n");
            fclose(file);
            return;
        }

        // Copy data into the new node
        temp->roll_no = roll_no;
        strcpy(temp->name, name);
        temp->gender = gender;
        strcpy(temp->phone_number, phone_number);
        temp->next = NULL;

        // Insert the new node at the end of the linked list
        if (*head == NULL) {
            *head = temp;
        } else {
            data *t1 = *head;
            while (t1->next != NULL) {
                t1 = t1->next;
            }
            t1->next = temp;
        }
    }

    fclose(file);
    printf("Data loaded from file successfully.\n");
}


int main(){

    int ch;
    data *head = NULL;
    int roll_num=0;
    while (1)
    {
        printf("\tMENU\n");
        printf("Enter your choice:\n");
        printf("0.exit\n");
        printf("1.Insert\n");
        printf("2.Display\n");
        printf("3.Modify\n");
        printf("4.Delete\n");
        printf("5.search\n");
        scanf("%d",&ch);
      
        switch (ch)
        {
        case 0:exit(0);
            
        case 1:insert(&head);
            break;
        case 2:display(head);
            break;
        case 3:modify(&head);
            break;
        case 4:printf("Enter Roll Number which to delete\n");
            scanf("%d",&roll_num);           
            delete(&head,roll_num);
            break;
        case 5:printf("Enter roll Number of student to search\n");
                scanf("%d",&roll_num);
                search(head,roll_num);
            break;
        
        default:printf("Invalid Choice\n");
            break;
        }
    }
    return 0;
}


