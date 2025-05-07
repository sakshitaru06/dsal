class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None

class HashTable:
    def __init__(self, size=10):
        self.size = size
        self.table = [None] * size

    def hash_function(self, key):
        return sum(ord(c) for c in key) % self.size

    def insert(self, key, value):
        index = self.hash_function(key)
        head = self.table[index]

        # Check for duplicate key
        temp = head
        while temp:
            if temp.key == key:
                print(f"Key '{key}' already exists. Use update instead.")
                return
            temp = temp.next

        new_node = Node(key, value)
        new_node.next = head
        self.table[index] = new_node
        print(f"Inserted ({key}, {value}) at index {index}")

    def find(self, key):
        index = self.hash_function(key)
        temp = self.table[index]
        while temp:
            if temp.key == key:
                print(f"Found at index {index}: {temp.key} -> {temp.value}")
                return temp.value
            temp = temp.next
        print("Key not found.")
        return None

    def delete(self, key):
        index = self.hash_function(key)
        temp = self.table[index]
        prev = None

        while temp:
            if temp.key == key:
                if prev:
                    prev.next = temp.next
                else:
                    self.table[index] = temp.next
                print(f"Deleted key: {key} from index {index}")
                return
            prev = temp
            temp = temp.next

        print("Key not found. Nothing deleted.")

    def display(self):
        print("\n--- Hash Table ---")
        for i, node in enumerate(self.table):
            print(f"Index {i}: ", end="")
            temp = node
            while temp:
                print(f"[{temp.key}: {temp.value}] -> ", end="")
                temp = temp.next
            print("None")

# === Example Usage ===
if __name__ == "__main__":
    ht = HashTable()
    while True:
        print("\n1. Insert")
        print("2. Find")
        print("3. Delete")
        print("4. Display")
        print("5. Exit")
        choice = input("Enter choice: ")

        if choice == '1':
            key = input("Enter key: ")
            value = input("Enter value: ")
            ht.insert(key, value)
        elif choice == '2':
            key = input("Enter key to find: ")
            ht.find(key)
        elif choice == '3':
            key = input("Enter key to delete: ")
            ht.delete(key)
        elif choice == '4':
            ht.display()
        elif choice == '5':
            break
        else:
            print("Invalid choice.")
