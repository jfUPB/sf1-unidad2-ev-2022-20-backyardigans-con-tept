using UnityEngine;
using System.IO.Ports;
using TMPro;

enum TaskState
{
    INIT,
    WAIT_COMMANDS
}

public class App : MonoBehaviour
{
    private static TaskState taskState = TaskState.INIT;
    private SerialPort _serialPort;
    private byte[] buffer;
    public TextMeshProUGUI Pulsador1;
    public TextMeshProUGUI Pulsador2;
    public TextMeshProUGUI Pulsador3;
    public TMP_Dropdown LedNumber;
    public TMP_Dropdown LedState;


    void Start()
    {
        _serialPort = new SerialPort();
        _serialPort.PortName = "/dev/ttyACM0";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable = true;
        _serialPort.NewLine = "\n";
        _serialPort.Open();
        Debug.Log("Open Serial Port");
        buffer = new byte[128];
    }

   void Update()
    {
        switch (taskState)
        {
            case TaskState.INIT:
                taskState = TaskState.WAIT_COMMANDS;
                Debug.Log("WAIT COMMANDS");
                break;
            case TaskState.WAIT_COMMANDS:
                
                if (_serialPort.BytesToRead > 0)
                {
                    string response = _serialPort.ReadLine();
                    Debug.Log(response);


                    if (response == "OFFOFFOFF")
                    {
                        Pulsador1.text = "RELEASED";
                        Pulsador2.text = "RELEASED";
                        Pulsador3.text = "RELEASED";
                        
                    }
                    else if (response == "OFFOFFON")
                    {
                        Pulsador1.text = "RELEASED";
                        Pulsador2.text = "RELEASED";
                        Pulsador3.text = "PUSHED";
                    }
                    else if (response == "OFFONOFF")
                    {
                        Pulsador1.text = "RELEASED";
                        Pulsador2.text = "PUSHED";
                        Pulsador3.text = "RELEASED";
                    }
                    else if (response == "OFFONON")
                    {
                         Pulsador1.text = "RELEASED";
                         Pulsador2.text = "PUSHED";
                         Pulsador3.text = "PUSHED";
                    }
                    else if (response == "ONOFFOFF")
                    {
                         Pulsador1.text = "PUSHED";
                         Pulsador2.text = "RELEASED";
                         Pulsador3.text = "RELEASED";
                    }
                    else if (response == "ONONOFF")
                    {
                         Pulsador1.text = "PUSHED";
                         Pulsador2.text = "PUSHED";
                         Pulsador3.text = "RELEASED";
                    }
                    else if (response == "ONONON")
                    {
                         Pulsador1.text = "PUSHED";
                         Pulsador2.text = "PUSHED";
                         Pulsador3.text = "PUSHED";
                    }
                    else if (response == "ONOFFON")
                    {
                        Pulsador1.text = "PUSHED";
                        Pulsador2.text = "RELEASED";
                        Pulsador3.text = "PUSHED";
                    }
            	 }

                break;
            default:
                Debug.Log("State Error");
                break;
        }
    }

    public void BTNREADBUTTONS()

    {
        _serialPort.Write("readBUTTONS\n");
        Debug.Log("Send readBUTTONS");
        
    }

    public void BTNREADLED()
    
    {
        if (LedNumber.options[LedNumber.value].text == "1")
        {
            if (LedState.options[LedState.value].text == "ON")
            {
                _serialPort.Write("led1ON\n");
                Debug.Log("Send led1ON");
            }
	    else
	    {
                _serialPort.Write("led1OFF\n");
                Debug.Log("Send led1OFF");
            }
        }
        else if (LedNumber.options[LedNumber.value].text == "2")
        {
            if (LedState.options[LedState.value].text == "ON")
            {
                _serialPort.Write("led2ON\n");
                Debug.Log("Send led2ON");
            } 
	    else 
	    {
                _serialPort.Write("led2OFF\n");
                Debug.Log("Send led2OFF");
            }

        }
        else if (LedNumber.options[LedNumber.value].text == "3")
        {
            if (LedState.options[LedState.value].text == "ON")
            {
                _serialPort.Write("led3ON\n");
                Debug.Log("Send led3ON");
            }
	    else 
	    {
                _serialPort.Write("led3OFF\n");
                Debug.Log("Send led3OFF");
            }

        }

    }

}

