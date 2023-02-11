import sqlite3
//The create_table() function creates a table named "users" if it doesn't already exist, with columns for id (a primary key, auto-incrementing integer), username, email, and password.

def create_table():
    conn = sqlite3.connect("users.db")
    c = conn.cursor()
    c.execute("""CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT,
                email TEXT,
                password TEXT)""")
    conn.commit()
    conn.close()

//The add_user() function inserts a new user into the "users" table with the specified username, email, and password.

def add_user(username, email, password):
    conn = sqlite3.connect("users.db")
    c = conn.cursor()
    c.execute("INSERT INTO users (username, email, password) VALUES (?, ?, ?)",
              (username, email, password))
    conn.commit()
    conn.close()
//The get_user() function returns the user record with the specified username.

def get_user(username):
    conn = sqlite3.connect("users.db")
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=?", (username,))
    user = c.fetchone()
    conn.close()
    return user
//The update_user() function updates the email and password of the user with the specified username.

def update_user(username, email, password):
    conn = sqlite3.connect("users.db")
    c = conn.cursor()
    c.execute("UPDATE users SET email=?, password=? WHERE username=?",
              (email, password, username))
    conn.commit()
    conn.close()
//The delete_user() function deletes the user with the specified username from the "users" table.

def delete_user(username):
    conn = sqlite3.connect("users.db")
    c = conn.cursor()
    c.execute("DELETE FROM users WHERE username=?", (username,))
    conn.commit()
    conn.close()
//Finally, the code creates a new user with username "johndoe", email "johndoe@example.com", and password "password123". It then retrieves and prints the user's information, updates the user's email and password, retrieves and prints the user's information again, and finally deletes the user from the database.

create_table()
add_user("johndoe", "johndoe@example.com", "password123")
user = get_user("johndoe")
print(user)
update_user("johndoe", "johndoe2@example.com", "password456")
user = get_user("johndoe")
print(user)
delete_user("johndoe")
user = get_user("johndoe")
print(user)
