class LamportClock:
    def __init__(self):
        self.time = 0

    def increment(self):
        self.time += 1

    def update(self, received_time):
        self.time = max(self.time, received_time) + 1

    def get_time(self):
        return self.time

    def send_message(self):
        self.increment()
        return self.time


if __name__ == "__main__":
    # Create three Lamport clock instances for three processes
    process1_clock = LamportClock()
    process2_clock = LamportClock()
    process3_clock = LamportClock()

    # Process 1 does some work
    process1_clock.increment()
    print(f"Process 1 time: {process1_clock.get_time()}")

    # Process 2 does some work
    process2_clock.increment()
    print(f"Process 2 time: {process2_clock.get_time()}")

    # Process 1 sends a message to Process 2
    sent_time = process1_clock.send_message()
    print(f"Process 1 sends message at time: {sent_time}")
    process2_clock.update(sent_time)
    print(f"Process 2 updated time: {process2_clock.get_time()}")

    # Process 2 sends a message to Process 3
    sent_time = process2_clock.send_message()
    print(f"Process 2 sends message at time: {sent_time}")
    process3_clock.update(sent_time)
    print(f"Process 3 updated time: {process3_clock.get_time()}")

    # Process 3 does some work
    process3_clock.increment()
    print(f"Process 3 time: {process3_clock.get_time()}")

    # Final clock values after communication
    print(f"Process 1 final time: {process1_clock.get_time()}")
    print(f"Process 2 final time: {process2_clock.get_time()}")
    print(f"Process 3 final time: {process3_clock.get_time()}")
    
    
# from threading import Thread
# import time
# import random

# class LamportClock:
#     def __init__(self, process_id):
#         self.process_id = process_id
#         self.time = 0
    
#     def tick(self):
#         """ Simulate an event, incrementing the Lamport timestamp """
#         self.time += 1
    
#     def update(self, received_time):
#         """ Update Lamport timestamp based on received time """
#         self.time = max(self.time, received_time) + 1
    
#     def get_time(self):
#         """ Return current Lamport timestamp """
#         return self.time
    
#     def __str__(self):
#         return f"LamportClock(process_id={self.process_id}, time={self.time})"

# def process(clock, other_clocks):
#     """ Simulate a process that interacts with other processes """
#     for _ in range(3):
#         time.sleep(random.uniform(0.2, 1.0))  # Simulate some computation time
#         clock.tick()
#         print(f"Process {clock.process_id}: Event occurred, time is now {clock.get_time()}")
        
#         # Simulate sending a message to another random process
#         receiver_id = random.choice(list(other_clocks.keys()))
#         received_time = other_clocks[receiver_id].get_time()
#         clock.update(received_time)
#         print(f"Process {clock.process_id}: Sent message to Process {receiver_id}, updated time to {clock.get_time()}")
#         print()

# # Number of processes
# NUM_PROCESSES = 3

# # Initialize Lamport clocks for each process
# clocks = {i: LamportClock(i) for i in range(NUM_PROCESSES)}

# # Start threads to simulate processes
# threads = []
# for process_id in range(NUM_PROCESSES):
#     thread = Thread(target=process, args=(clocks[process_id], {pid: clocks[pid] for pid in clocks if pid != process_id}))
#     threads.append(thread)
#     thread.start()

# # Wait for all threads to complete
# for thread in threads:
#     thread.join()

# # Print final state of clocks
# print("\nFinal state of clocks:")
# for process_id in range(NUM_PROCESSES):
#     print(clocks[process_id])

