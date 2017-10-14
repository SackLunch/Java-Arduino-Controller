package arduino;

import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import com.fazecast.jSerialComm.SerialPort;
import java.awt.GridLayout;
import java.io.PrintWriter;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JLabel;
import javax.swing.SwingConstants;
import java.awt.Font;

/**
 * CLASS:			This class will launch the GUI.
 */
public class Arduino extends JFrame 
{
	//Fields
	/** * FIELD:		Serial version for this class. */
	private static final long serialVersionUID = 1L;
	/** * FIELD:		SerialPort object. */
	private SerialPort comPort;
	/** * FIELD:		The comport that will be used.  Change this field if you're using a different port for your Arduino. */
	private String comPortName = "COM3";
	/** * FIELD:		Communication rate for the USB port.  If you're Arduino is using a different rate, change this value to match it. */
	private int baudRate = 9600;
	/** * FIELD:		PrintWriter used to write through the USB port. */
	static PrintWriter outPut;
	/** * FIELD:		Main content pane. */
	private JPanel contentPane;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Arduino frame = new Arduino();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public Arduino() {
		setTitle("Arduino");
		//Choose what happens when the 'x' is clicked.
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//Set the size of the GUI.
		setBounds(100, 100, 246, 162);
		//Create a new contentPane and set the borders
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new GridLayout(3, 0, 0, 0));
		
		//Create a new JPanel
		JPanel panel = new JPanel();
		contentPane.add(panel);
				
		//Add connect button.
		JButton btnConnect = new JButton("Connect");
		panel.add(btnConnect);
		
		//Add disconnect button.
		JButton btnDisconnect = new JButton("Disconnect");
		panel.add(btnDisconnect);
		
		//Add another panel for the middle row.
		JPanel panel_1 = new JPanel();
		contentPane.add(panel_1);
		
		//Add the on button.
		JButton btnOn = new JButton("On");
		panel_1.add(btnOn);
		
		//Add the blink button.
		JButton btnBlink = new JButton("Blink");
		panel_1.add(btnBlink);
		
		//Add the off button.
		JButton btnOff = new JButton("Off");
		panel_1.add(btnOff);

		//Add the status JLabel.
		JLabel lblStatus = new JLabel("Status:");
		lblStatus.setFont(new Font("Tahoma", Font.PLAIN, 18));
		lblStatus.setHorizontalAlignment(SwingConstants.LEFT);
		contentPane.add(lblStatus);
		
		//Listener for connect button.
		btnConnect.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) 
			{
				//Set up the values for the USB port.
				comPort = SerialPort.getCommPort(comPortName);
				comPort.setBaudRate(baudRate);
					
				//If the port is not closed, open the USB port.
				if(comPort.isOpen() == false)
				{	
					try 
					{
						//Open the USB port and initialize the PrintWriter.
						comPort.openPort();
						Thread.sleep(1000);
						outPut = new PrintWriter(comPort.getOutputStream());
					} 
					
					catch(Exception c){}
					
					//Update the console and status.
					System.out.println("Connection to Arduino successful.");
					lblStatus.setText("Status: Connected");
					
				}
				else 
				{
					//If the port couldn't be opened print out to the console.
					System.out.println("Error opening port.");
					lblStatus.setText("Status: Opening USB failed");
				}
			}
		});
		
		//Listener for the disconnect button.
		btnDisconnect.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) 
			{
				//Close the USB port if it's open.
				if(comPort.isOpen() == true)
				{	
					//Close the port and update the console/status.
					comPort.closePort();
					System.out.println("Disconnected from Arduino.");
					lblStatus.setText("Status: Disconnected");
				}
			}
		});
		
		//Listener for the on button.
		btnOn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) 
			{
				//Turns on the #13 pin LED.
				if(comPort.isOpen() == true)
				{
					//Send a 1 to the Arduino and update the user.
					System.out.println("Status: LED on");
					lblStatus.setText("Status: LED on");
					outPut.print("1");
					outPut.flush();
				}
				else
				{
					//Update the status/console if the Arduino hasn't been connected.
					System.out.println("Connect Arduino");
					lblStatus.setText("Status: Connect Arduino");
				}
			}
		});
		
		//Listener for the blink button.
		btnBlink.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) 
			{
				//Turns on the #13 pin LED and flashes it 10 times.
				if(comPort.isOpen() == true)
				{
					//Send a 2 to the Arduino and update the user.
					System.out.println("Status: LED blinking");
					lblStatus.setText("Status: LED blinking");
					outPut.print("2");
					outPut.flush();
				}
				else
				{
					//Update the status/console if the Arduino hasn't been connected.
					System.out.println("Connect Arduino");
					lblStatus.setText("Status: Connect Arduino");
				}
			}
		});
		
		//Listener for the off button.
		btnOff.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) 
			{
				//Turns off the #13 pin LED.
				if(comPort.isOpen() == true)
				{
					//Send a 3 to the Arduino and update the user.
					System.out.println("Status: LED off");
					lblStatus.setText("Status: LED off");
					outPut.print("3");
					outPut.flush();
				}
				else
				{
					//Update the status/console if the Arduino hasn't been connected.
					System.out.println("Connect Arduino");
					lblStatus.setText("Status: Connect Arduino");
				}
			}
		});
	}

}
