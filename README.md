# Thread Hijacking Collection
Collection of Thread Hijacking malware with different techniques. This code is for educational purposes only, do not use it for any malicious or unauthorized activity.

# 💻 Code

It's a simple shellcode injection into a thread of a target process, first the payload is decrypted, for a better view of the encryption check out the encoding mechanism [here](https://github.com/Hue-Jhan/Simple-shellcode-crypter), then the code takes a handle to the target process, and finds a thread inside it. Once a thread is found/created, the program will allocate memory for the payload, upload the shellcode in it, and change its permissions to RWX.

Now we get to the actual execution: first we suspend the thread, then we change its instruction pointer to make it point to our payload, and we resume the thread. There are multiple ways of achieving the thread hijacking malware, here are the ones i made:

### 1) Find an existing thread
As previously explained, this version finds and hijacks an already existing thread inside a target process, this could be dangerous as the thread in question might hold sensitive operations, there is a high chance that after executing our new payload the process might crash, because it cannot function without the thread we hijacked.  

In order to do this we can use ```CreateToolhelp32Snapshot()``` to list all existing processes, once we find the one that matches the name, we save its pid and we get a handle with ```OpenProcess()``` and the correct permissions.

Then we do the same thing but iterating through all the threads of our system, and we target the first thread whose owner is the process we targeted earlier. We save its tid and get a handle with ```OpenThread()```. 

After handling the payload part which i described earlier, we suspend the thread, change its RIP to point to the payload, and resume it. After executing the shellcode the thread will end...

### 2) Create a new thread
2 - Create and hijack a new thread inside a target process

### 3) DLL
3 - Both options but in a DLL, stealthier 

a

# 🛡 AV Detection


<img align="right" src="media/hijak2create.png" width="280" />

a

<img src="media/hijak2create-reshack.png" width="350" />

a

a

a

<img align="right" src="media/hijak2bet.png" width="280" />

a

<img src="media/hijak2bet-reshack.png" width="350" />

a

a

a

<img align="right" src="media/dll-hijak-find.png" width="280" />

a

<img src="media/dll-hijak-find-reshack.png" width="350" />

a

