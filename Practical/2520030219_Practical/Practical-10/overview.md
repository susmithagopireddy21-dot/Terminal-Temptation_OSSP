# Practical 10 – Inode Structures and Memory-Mapped I/O

## Aim

To investigate inode structures using Linux commands, create hard and symbolic links, and implement file reading and writing using `mmap()`.

## Part 1: Inode Investigation

### Commands Used

```bash
ls -i original.txt
stat original.txt
ls -li original.txt hardlink.txt symlink.txt
find . -inum 53314
find . -type l -ls
```

### Hard Link

A hard link is another directory entry that points to the same inode as the original file.

The original file and hard link had the same inode number:

```bash
original.txt  -> inode 53314
hardlink.txt  -> inode 53314
```

The link count became 2 after creating the hard link.

### Symbolic Link

A symbolic link is a separate file that stores a reference to another file.

```bash
symlink.txt -> original.txt
```

The symbolic link had a different inode:
```bash
symlink.txt -> inode 53346
```

## Part 2: Memory-Mapped I/O
### Program

The C program mmap_file.c uses the mmap() system call to map a file into the process address space.

The program:

Opens or creates mmap.txt.
Writes initial content to the file.
Maps the file into memory using mmap().
Reads the content through the mapped memory.
Modifies the first character.
Uses msync() to synchronize the changes.
Unmaps the file using munmap().

Output:
```c
Original content: Hello from mmap!
Modified content: hello from mmap!
```

The modified content was also verified in mmap.txt:
```c
hello from mmap!
```

### mmap() vs read()/write()
mmap()	read()/write()
Maps a file into memory	Uses explicit read/write system calls
File can be accessed through memory addresses	Data is transferred using buffers
Convenient for memory-based access	Simple and straightforward
Useful for random access to mapped data	Commonly used for sequential I/O
Requires mmap() and munmap()	Uses read() and write()
Implementation is slightly more complex	Implementation is generally simpler


##Result

The inode structure of files was successfully investigated. Hard links and symbolic links were created and their inode differences were observed. A C program using mmap() was successfully implemented to read and modify file contents.

```text
Save:

**Ctrl + O → Enter → Ctrl + X**

---

### STEP 2 — Check your files

Run:

```bash
ls -l
```


