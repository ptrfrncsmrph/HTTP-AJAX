import React, { FormEventHandler } from "react"
import axios from "axios"

interface NewFriendFormProps {
  handleClick: FormEventHandler
}

export default ({ handleClick }: NewFriendFormProps) => {
  return (
    <form>
      <button onClick={handleClick}>Add new friend</button>
    </form>
  )
}
