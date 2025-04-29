from graphviz import Digraph

dot = Digraph(comment='Event Planner and Budget Tracker System Workflow')

# Nodes
dot.node('A', 'Start\n(main)')
dot.node('B', 'Login\n(login())')
dot.node('C', 'Welcome Screen\n(welcome())')
dot.node('D', 'Main Menu\n(main_menu())')
dot.node('E1', 'Create New Event\n(newEvent())')
dot.node('E2', 'Manage Existing Event\n(existingEvent())')
dot.node('E3', 'Exit')

# Create Event Branch
dot.node('F1', 'Enter Event Details\n(enterEventDetails())')
dot.node('F2', 'Add Attendees\n(addAttendeeList())')
dot.node('F3', 'Choose Venue & Services\n(chooseVenueAndServices())')
dot.node('F4', 'Save Data\n(event.csv, attendees.csv, etc.)')

# Manage Event Branch
dot.node('G1', 'Select Event')
dot.node('G2', 'Display Event Details\n(displayEventDetails())')
dot.node('G3', 'Update Event\n(updateExistingEvent())')
dot.node('G4', 'Update Details/Add Attendees')

# Edges
dot.edges(['AB', 'BC', 'CD'])
dot.edge('D', 'E1', label='1')
dot.edge('D', 'E2', label='2')
dot.edge('D', 'E3', label='3 (Exit)')

# Create Event Flow
dot.edge('E1', 'F1')
dot.edge('F1', 'F2')
dot.edge('F2', 'F3')
dot.edge('F3', 'F4')
dot.edge('F4', 'D', label='Back to Menu')

# Manage Event Flow
dot.edge('E2', 'G1')
dot.edge('G1', 'G2', label='View')
dot.edge('G1', 'G3', label='Update')
dot.edge('G3', 'G4')
dot.edge('G4', 'D', label='Back to Menu')

# Render the graph (optional)
dot.render('event_workflow', format='png', view=True)

print(dot.source)