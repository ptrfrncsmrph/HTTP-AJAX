import React, { FormEventHandler } from "react"
import axios from "axios"

export default () => {
  const handleClick: FormEventHandler = event => {
    event.preventDefault()
    axios.post("http://10.0.0.53:5000/friends", {
      name: "Person",
      age: 72,
      email: "user@email.com"
    })
  }
  return (
    <form>
      <button onClick={handleClick}>Add new friend</button>
    </form>
  )
}
