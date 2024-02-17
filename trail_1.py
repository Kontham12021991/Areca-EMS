import multiprocessing
import schedule
import time
import serial

def send_uart_data(data_to_send, uart_port, baudrate, result_queue):
    try:
        port = serial.Serial(uart_port, baudrate, timeout=1)
        port.write(data_to_send.encode('utf-8'))
        port.close()  # Close the port after sending data
        result_queue.put("Sent data successfully")
    except Exception as e:
        result_queue.put(f"Error in send_uart_data: {e}")

def receive_uart_data(uart_port, baudrate, result_queue):
    try:
        port = serial.Serial(uart_port, baudrate, timeout=1)
        received_data = port.readline()
        port.close()
        result_queue.put(f"Received data: {received_data.decode('utf-8')}")
    except Exception as e:
        result_queue.put(f"Error in receive_uart_data: {e}")

def schedule_send_receive(data_to_send, uart_port, baudrate):
    # Create a multiprocessing Queue for communication
    queue = multiprocessing.Queue()

    # Create separate processes for sending and receiving data
    receive_process = multiprocessing.Process(target=receive_uart_data, args=(uart_port, baudrate, queue))
    send_process = multiprocessing.Process(target=send_uart_data, args=(data_to_send, uart_port, baudrate, queue))

    # Start the send process
    send_process.start()

    # Wait for a short delay before starting the receive process
    time.sleep(0.2)  # Adjust the delay as needed

    # Start the receive process
    receive_process.start()

    # Wait for both processes to finish
    send_process.join()
    receive_process.join()

    # Retrieve results from the queue
    while not queue.empty():
        result = queue.get()
        print(result)

if __name__ == "__main__":
    uart_port = 'COM1'
    baudrate = 9600

    for data_point in ['Kavach Project uart program']:
        schedule.every(0.030).seconds.do(schedule_send_receive, data_point, uart_port, baudrate)

    while True:
        schedule.run_pending()
        time.sleep(0.005)
