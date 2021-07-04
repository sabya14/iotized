import React from 'react';
import {makeStyles} from '@material-ui/core/styles';
import Title from './Title';
import {QuadStateView} from "../QuadState";
import Button from "@material-ui/core/Button";
import CircularProgress from "@material-ui/core/CircularProgress";
import {changeDirection} from "../data/arduino-rc";
import ArrowUpwardIcon from '@material-ui/icons/ArrowUpward';
import ArrowDownwardIcon from '@material-ui/icons/ArrowDownward';
import ArrowForwardIcon from '@material-ui/icons/ArrowForward';
import ArrowBackwardIcon from '@material-ui/icons/ArrowBack';

function preventDefault(event) {
    event.preventDefault();
}

const useStyles = makeStyles({
    depositContext: {
        flex: 1,
    },
});

const ControlButtons = ({trigger}) => <div>
    <Button onClick={() => trigger("down")}><ArrowDownwardIcon/></Button>
    <Button onClick={() => trigger("up")}><ArrowUpwardIcon/></Button>
    <Button onClick={() => trigger("left")}><ArrowBackwardIcon/></Button>
    <Button onClick={() => trigger("right")}><ArrowForwardIcon/></Button>
</div>;


export default function CarControl() {
    const createOperation = (direction) => changeDirection({direction , speed: 0.5})
    return (
        <React.Fragment>
            <Title>Arduino-1 Car Control</Title>
            <QuadStateView
                sideEffectFn={createOperation}
                initComponentFn={
                    (_, trigger) => <ControlButtons trigger={trigger}/>
                }
                inProgressComponentFn={
                    () =>
                        <Button variant="contained"
                                color="primary"
                                disabled
                        >
                            <CircularProgress/>
                        </Button>
                }
                successComponentFn={
                    ({data}, trigger, reset) => <ControlButtons trigger={trigger}/>
                }
                errorComponentFn={
                    ({error}, trigger, reset) => <ControlButtons trigger={trigger}/>

                }
            />
        </React.Fragment>
    );
}
